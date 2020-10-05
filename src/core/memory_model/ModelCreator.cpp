//
// Created by denis on 02.10.20.
//

#include "ModelCreator.h"

std::unique_ptr<TaskModelInterface> ModelCreator::CreateModel() {
    auto storage =      std::make_unique<TaskStorage>();
    auto view_time =    std::make_unique<DatePriorityView>();
    auto view_label =   std::make_unique<TagPriorityView>();
    auto handler =      std::make_unique<LinkManager>(*view_time, *view_label);
    return std::make_unique<TaskModel>(
            std::move(storage),
            std::move(view_time),
            std::move(view_label),
            std::move(handler));
}
