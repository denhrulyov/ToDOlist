//
// Created by denis on 23.09.20.
//

#ifndef TODOLIST_TASKRESPOSITORY_H
#define TODOLIST_TASKRESPOSITORY_H

#include "core/memory_model/data/TaskIDFactory.h"
#include "TaskRepositoryInterface.h"

class TaskRespository : public TaskRepositoryInterface {

public:
    TaskRespository(
            std::unique_ptr<TaskStorageInterface>                   storage,
            std::unique_ptr<PriorityViewInterface<BoostDate>>       view_date,
            std::unique_ptr<PriorityViewInterface<std::string>>     view_label,
            std::unique_ptr<LinkManagerInterface>                   link_manger)
    :
    storage_(std::move(storage)),
    by_date_(std::move(view_date)),
    by_label_(std::move(view_label)),
    link_manager_(std::move(link_manger))
    {}

public:
    TaskCreationResult                          addTask(const RepositoryTaskDTO&) override;
    TaskCreationResult                          addSubTask(TaskID, const RepositoryTaskDTO&) override;
    TaskModificationResult                      setTaskData(TaskID, const RepositoryTaskDTO&) override;
    std::optional<RepositoryTaskDTO>            getTaskData(TaskID) const override;
    TaskModificationResult                      dropTask(TaskID) override;
    TaskModificationResult                      setCompleted(TaskID) override;
    std::vector<RepositoryTaskDTO>              getToDate(const BoostDate &date_to) const override;
    std::vector<RepositoryTaskDTO>              getWithLabel(const std::string &label) const override;
    std::vector<RepositoryTaskDTO>              getSubTasks(TaskID id) const override;
    std::vector<RepositoryTaskDTO>              getSubTasksRecursive(TaskID id) const override;
    std::vector<RepositoryTaskDTO>              getAllTasks() const override;
    std::optional<RepositoryTaskDTO>            getParentTask(TaskID id) const override;

private:
    std::unique_ptr<TaskStorageInterface>                   storage_;
    TaskIDFactory                                           id_generator_;
    std::unique_ptr<PriorityViewInterface<BoostDate>>       by_date_;
    std::unique_ptr<PriorityViewInterface<std::string>>     by_label_;
    std::unique_ptr<LinkManagerInterface>                   link_manager_;
};


std::vector<RepositoryTaskDTO> convertAllNodes(const std::vector<std::weak_ptr<TaskNode>>& all);
std::vector<RepositoryTaskDTO> get_children_recurse(const std::shared_ptr<TaskNode>& node);

#endif //TODOLIST_TASKRESPOSITORY_H
