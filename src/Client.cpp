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
            : stub_(GrpcTaskService::NewStub(channel)) {}

    void Run() {

    }
private:

    std::unique_ptr<GrpcTaskService::Stub> stub_;
};


int main() {
    std::string server_address("0.0.0.0:50051");
    ToDOListClient client(grpc::CreateChannel(
            server_address, grpc::InsecureChannelCredentials()));
    client.Run();
    return 0;
}
