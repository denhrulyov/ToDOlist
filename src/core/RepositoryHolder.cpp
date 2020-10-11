//
// Created by denis on 04.10.20.
//

#include "RepositoryHolder.h"

RepositoryHolder::RepositoryHolder(
        std::unique_ptr<RepositoryCreator> creator,
        std::unique_ptr<PersisterCreator> persister_creator) :
        creator_(std::move(creator)),
        persister_creator_(std::move(persister_creator))
        {
            model_ = creator_->CreateModel();
        }


TaskRepositoryInterface &RepositoryHolder::GetModel() {
    return *model_;
}

bool RepositoryHolder::LoadModelFromFile(const std::string &filepath) {
    auto file = std::make_shared<std::fstream>(filepath, std::ios::in);
    if (!file->is_open()) {
        return false;
    }
    auto new_model = creator_->CreateModel();
    auto persister = persister_creator_->CreatePersister(*new_model, file);
    if (!persister->Load()) {
        return false;
    }
    std::swap(model_, new_model);
    return true;
}

bool RepositoryHolder::SaveModelToFile(const std::string &filepath) {
    auto file = std::make_shared<std::fstream>(filepath, std::ios::out);
    if (!file->is_open()) {
        return false;
    }
    auto persister = persister_creator_->CreatePersister(*model_, file);
    return persister->Save();
}

