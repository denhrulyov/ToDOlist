//
// Created by denis on 04.10.20.
//

#include "ModelHolder.h"

ModelHolder::ModelHolder(
        std::unique_ptr<ModelCreator> creator,
        std::unique_ptr<ModelPersister> persister,
        StreamOwner &persistence_stream) :
        creator_(std::move(creator)),
        persister_(std::move(persister)),
        persistence_stream_(persistence_stream)
        {}


TaskModelInterface &ModelHolder::GetModel() {
    if (!model_) {
        model_ = creator_->CreateModel();
    }
    return *model_;
}

bool ModelHolder::LoadModelFromFile(const std::string &filepath) {
    auto file = std::make_unique<std::fstream>(filepath, std::ios::in);
    if (!file->is_open()) {
        return false;
    }
    auto new_model = creator_->CreateModel();
    persistence_stream_.SetStream(std::move(file));
    if (!persister_->Load(*new_model)) {
        return false;
    }
    std::swap(model_, new_model);
    return true;
}

bool ModelHolder::SaveModelToFile(const std::string &filepath) {
    auto file = std::make_unique<std::fstream>(filepath, std::ios::out);
    if (!file->is_open()) {
        return false;
    }
    persistence_stream_.SetStream(std::move(file));
    return persister_->Save(*model_);
}

