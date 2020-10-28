//
// Created by denis on 09.09.20.
//

#include "TODOList.h"

std::unique_ptr<TaskServiceInterface> todo_list::createService() {
    std::string server_address("0.0.0.0:50051");
    return
    std::make_unique<GrpcTaskServiceAdaptor>(
            GrpcTaskService::NewStub(grpc::CreateChannel(
            server_address, grpc::InsecureChannelCredentials())));
}
