//
// Created by denis on 04.10.20.
//

#include "RepositoryHolder.h"
#include <future>

RepositoryHolder::RepositoryHolder(
        std::unique_ptr<RepositoryCreator> creator,
        std::unique_ptr<PersisterCreator> persister_creator) :
        creator_(std::move(creator)),
        persister_creator_(std::move(persister_creator))
        {
            repository_ = creator_->CreateModel();
        }


TaskRepositoryInterface &RepositoryHolder::GetRepository() {
    return *repository_;
}

bool RepositoryHolder::LoadRepositoryFromFile(const std::string &filepath) {
    auto file = std::make_shared<std::fstream>(filepath, std::ios::in);
    if (!file->is_open()) {
        return false;
    }
    auto new_model = creator_->CreateModel();
    auto persister = persister_creator_->CreatePersister(*new_model, file);
    std::future<bool> is_loaded = std::async(std::bind(&Persister::Load, persister.get()));
    is_loaded.wait();
    if (!is_loaded.get()) {
        return false;
    }
    std::swap(repository_, new_model);
    return true;
}

bool RepositoryHolder::SaveRepositoryToFile(const std::string &filepath) {
    auto file = std::make_shared<std::fstream>(filepath, std::ios::out);
    if (!file->is_open()) {
        return false;
    }
    auto persister = persister_creator_->CreatePersister(*repository_, file);
    std::future<bool> is_saved = std::async(std::bind(&Persister::Save, persister.get()));
    is_saved.wait();
    return is_saved.get();
}

