//
// Created by denis on 22.10.20.
//

#include "core/api/GrpcTaskServiceImpl.h"

int main() {
    std::string server_address("0.0.0.0:50051");
    grpc::EnableDefaultHealthCheckService(true);
    grpc::reflection::InitProtoReflectionServerBuilderPlugin();
    GrpcTaskServiceImpl service(
            std::make_unique<RepositoryHolder>(
                    std::make_unique<RepositoryCreator>(),
                    std::make_unique<PersisterCreator>()));
    ServerBuilder builder;
    // Listen on the given address without any authentication mechanism.
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    // Register "service" as the instance through which we'll communicate with
    // clients. In this case it corresponds to an *synchronous* service.
    builder.RegisterService(&service);
    // Finally assemble the server.
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    // Wait for the server to shutdown. Note that some other thread must be
    // responsible for shutting down the server for this call to ever return.
    server->Wait();
    return 0;
}