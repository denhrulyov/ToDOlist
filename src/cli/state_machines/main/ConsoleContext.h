//
// Created by denis on 18.08.20.
//

#ifndef TODOLIST_CONSOLECONTEXT_H
#define TODOLIST_CONSOLECONTEXT_H


#include "ConsoleContextInterface.h"
class State;


class ConsoleContext : public ConsoleContextInterface {

public:
    explicit
    ConsoleContext( std::unique_ptr<TaskServiceInterface>,
                    std::unique_ptr<ConsoleIOInterface>,
                    std::unique_ptr<OstreamServiceSerializer>,
                    std::unique_ptr<IstreamServiceDeserializer>);

public:
    void                                    setTaskService(std::unique_ptr<TaskServiceInterface>) override;
    TaskServiceInterface&                   getTaskService() override;
    ConsoleIOInterface &                    getIO() override;
    std::map<TaskNumber, TaskID>&           getMatchingTablePositionToID() override;
    std::map<TaskID, TaskNumber>&           getMatchingIDtoTablePosition() override;

public:
    void                                    fillTaskBuffer(const TaskDTO&) override;
    std::optional<TaskDTO>                  getTaskBuffer() override;
    void                                    fillIDBuffer(TaskID) override;
    std::optional<TaskID>                   getBufferedId() const override;
    OstreamServiceSerializer&               getSerializer() override;
    IstreamServiceDeserializer&             getDeserializer() override;

public:
    void                                    fillTable(const std::vector<TaskDTO>&) override;

private:


    std::map<TaskNumber, TaskID>            task_table_;
    std::map<TaskID, TaskNumber>            id_table_;
    std::unique_ptr<ConsoleIOInterface>     io_;

private:
    std::optional<TaskID>                   id_buffer_;
    std::optional<TaskDTO>                  task_buffer_;
    std::unique_ptr<TaskServiceInterface>   service_;
    std::unique_ptr<OstreamServiceSerializer>       serializer_;
    std::unique_ptr<IstreamServiceDeserializer>     deserializer_;
};



#endif //TODOLIST_CONSOLECONTEXT_H
