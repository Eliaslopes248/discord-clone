// Jest setup file to start server before tests
const { server } = require("../rest_server");

// Wait for server to be ready before running tests
beforeAll((done) => {
    // Check if server is already listening
    if (server.listening) {
        console.log("Server already listening, proceeding with tests");
        done();
    } else {
        // Wait for server to start listening
        server.once("listening", () => {
            console.log("Server started, proceeding with tests");
            done();
        });
    }
}, 10000); // 10 second timeout

// Close server after all tests
afterAll((done) => {
    if (server && server.listening) {
        server.close(() => {
            console.log("Server closed after tests");
            done();
        });
    } else {
        done();
    }
}, 5000); // 5 second timeout

