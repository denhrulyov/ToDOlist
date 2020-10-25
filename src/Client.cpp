//
// Created by denis on 22.10.20.
//

#include <iostream>
#include <memory>
#include <string>


#include <grpcpp/grpcpp.h>


using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

#include "core/persistence/ProtoConvert.h"
#include "TaskService.grpc.pb.h"

class ToDOListClient {

public:
    explicit ToDOListClient(const std::shared_ptr<Channel>& channel)
            : stub_(GrpcTaskService::NewStub(channel)), status(Status::OK) {}

    // Assembles the client's payload, sends it and presents the response back
    // from the server.
    std::optional<TaskData> GetTaskByID(uint32_t id) {
        // Data we are sending to the server.
        TaskIdMessage request;
        request.set_id(id);

        // Container for the data we expect from the server.
        GetTaskByIDResponse reply;
        // Context for the client. It could be used to convey extra information to
        // the server and/or tweak certain RPC behaviors.
        ClientContext context;

        // The actual RPC.
        status = stub_->GetTaskByID(&context, request, &reply);

        // Act upon its status.
        if (status.ok()) {
            if (reply.has_task()) {
                return reply.task();
            } else {
                return std::nullopt;
            }
        } else {
            std::cout << status.error_code() << ": " << status.error_message()
                      << std::endl;
            return std::nullopt;
        }
    }
    AddTaskResponse AddTask(const TaskData& task) {
        // Data we are sending to the server.
        const TaskData request = task;

        // Container for the data we expect from the server.
        AddTaskResponse reply;
        // Context for the client. It could be used to convey extra information to
        // the server and/or tweak certain RPC behaviors.
        ClientContext context;

        // The actual RPC.
        status = stub_->AddTask(&context, request, &reply);

        // Act upon its status.
        if (status.ok()) {
            return reply;
        } else {
            std::cout << status.error_code() << ": " << status.error_message()
                      << std::endl;
        }
        return reply;
    }
    Status status;
private:

    std::unique_ptr<GrpcTaskService::Stub> stub_;
};


int main() {
    std::string server_address("0.0.0.0:50051");
    ToDOListClient greeter(grpc::CreateChannel(
            server_address, grpc::InsecureChannelCredentials()));
    int i = 0;
    while (greeter.status.ok() && ++i) {
        std::cin.clear();
        if (i% 2 == 0) {
            std::cout << "Input id" << std::endl;
            uint32_t id;
            std::cin >> id;
            auto resp = greeter.GetTaskByID(id);
            if (!resp) {
                std::cout << "bad : no task" << std::endl;
            } else {
                std::cout << resp.value().name() << std::endl;
            }
        }
        if (i %2 == 1) {
            std::cout << "Input task" << std::endl;
            std::string name;
            int prior;
            std::string label;
            std::string s_date;
            std::cin >> name >> prior >> label >> s_date;
            BoostDate date = boost::gregorian::from_simple_string(s_date);
            TaskData task;
            task.set_name(name);
            task.set_prior(static_cast<TaskData::Priority>(prior));
            task.set_label(label);
            auto pb_date = proto_convert::GetProtobufDate(date);
            task.set_allocated_date(pb_date.release());
            task.set_completed(false);
            auto resp = greeter.AddTask(task);
            if (!resp.success()) {
                std::cout << "bad : " << resp.error_msg() << std::endl;
            } else {
                std::cout << resp.created_id().id() << std::endl;
            }
        }
    }
    return 0;
}
