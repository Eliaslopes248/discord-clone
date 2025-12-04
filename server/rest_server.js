//===================================================================================
// IMPORT MODULES
//===================================================================================
const express           = require("express");
const bodyParser        = require("body-parser");
const cors              = require("cors");
const { loadEnvFile }   = require("./utils/env");

// Load environment variables
loadEnvFile();
// create app instance
const app           = express();
const PORT          = process.env.REST_PORT || process.env.PORT || 8000;

// ====================================================
// ADD MIDDLEWARE
// ====================================================
const allowedOrigins = process.env.ALLOWED_ORIGINS ? process.env.ALLOWED_ORIGINS.split(',') : ['http://localhost:3000', 'http://localhost:8000', 'http://localhost:8080'];

app.use(cors({
    origin: function(origin, callback) {
        // Allow requests with no origin (like mobile apps or curl)
        if (!origin) {
            console.log("CORS: Allowing request with no origin");
            return callback(null, true);
        }
        
        console.log("CORS: Request from origin:", origin);
        console.log("CORS: Allowed origins:", allowedOrigins);
    
        if (allowedOrigins.includes(origin)) {
            console.log("CORS: Origin allowed");
            callback(null, true);
        } else {
            console.log("CORS: Origin not allowed");
            callback(new Error('Not allowed by CORS'));
        }
    },
    methods: ['POST', 'GET', 'OPTIONS'],
    credentials: true
}));

app.use((req, res, next) => {
    res.setHeader("Cross-Origin-Opener-Policy", "same-origin-allow-popups");
    res.setHeader("Cross-Origin-Embedder-Policy", "same-origin-allow-popups"); 
    next();
});

// Log all incoming requests
app.use((req, res, next) => {
    console.log(`\n[${new Date().toISOString()}] ${req.method} ${req.path}`);
    console.log("Headers:", JSON.stringify(req.headers, null, 2));
    next();
});

app.use(bodyParser.urlencoded({extended:true, limit: '50mb'}));
app.use(express.json({limit: '50mb'}));  

// Error handling middleware for CORS
app.use((err, req, res, next) => {
    if (err.message === 'Not allowed by CORS') {
        console.error("CORS Error:", err.message);
        console.error("Request origin:", req.headers.origin);
        return res.status(403).json({ error: 'CORS policy violation', origin: req.headers.origin });
    }
    next(err);
});

// General error handling middleware for async routes
app.use((err, req, res, next) => {
    console.error("Unhandled error:", err);
    if (!res.headersSent) {
        res.status(500).json({ 
            error: 'Internal server error',
            message: err.message 
        });
    }
});

// ====================================================
// IMPORT ROUTES MODULES
// ====================================================
const authRoutes = require("./routes/auth");


// ====================================================
// ADD ROUTES
// ====================================================
app.use("/", authRoutes);

// ====================================================
// INIT ROUTE
// ====================================================
app.get("/", (req, res)=> {
    res.status(200).send({});
});


// endpoint to test api connection
app.get("/test/connection", (req, res)=>{
    console.log("Endpoint reached!");
    console.log("Request headers:", req.headers);
    console.log("Request method:", req.method);
    res.status(200).json({status:200, message: "connected!"});
});

app.post("/test/post", (req, res)=>{
    console.log("Endpoint reached!");
    console.log("Request headers:", req.headers);
    console.log("Request method:", req.method);
    console.log("Request body:", req.body);

    res.status(200).json({status:200, message: "connected!"});
});


// ====================================================
// SERVER LISTENING
// ====================================================
const server = app.listen(PORT, ()=>{
    console.log("--------------------------\n");
    console.log("REST API LISTENING");
    console.log("PORT:", PORT);
    console.log("\n--------------------------");
});

// Export app and server for testing
module.exports = { app, server };