/**
 * use helpers to access .env files and variables
 */

const dotenv = require("dotenv");
const path = require('path');

/**
 * Loads the appropriate .env file based on NODE_ENV
 * @param {string} baseDir - Base directory path (defaults to server root)
 * @returns {object} Result object from dotenv.config()
 */
function loadEnvFile(baseDir = null) {
    // If baseDir not provided, assume this file is in utils/ and go up one level
    const envDir = baseDir || path.join(__dirname, '../env');
    
    // Default env file
    let envFile = path.join(envDir, '.env');
    
    // If NODE_ENV is already set, use it directly
    if (process.env.NODE_ENV) {
        if (process.env.NODE_ENV === 'prod' || process.env.NODE_ENV === 'production') {
            envFile = path.join(envDir, '.env.production');
        } else if (process.env.NODE_ENV === 'dev' || process.env.NODE_ENV === 'development') {
            envFile = path.join(envDir, '.env.developement');
        }
        
        // Load the environment file
        const result = dotenv.config({ path: envFile });
        if (result.error) {
            console.warn("Warning: Could not load .env file:", result.error.message);
        }
        return result;
    }
    
    // No system NODE_ENV, load default .env first to get NODE_ENV
    const result = dotenv.config({ path: envFile });
    if (result.error) {
        console.warn("Warning: Could not load .env file:", result.error.message);
        return result;
    }
    
    // Now choose environment file based on loaded NODE_ENV
    if (process.env.NODE_ENV === 'prod' || process.env.NODE_ENV === 'production') {
        envFile = path.join(envDir, '.env.production');
    } else if (process.env.NODE_ENV === 'dev' || process.env.NODE_ENV === 'development') {
        envFile = path.join(envDir, '.env.developement');
    }
    
    // Reload with the correct environment file
    const reloadResult = dotenv.config({ path: envFile, override: true });
    if (reloadResult.error) {
        console.warn("Warning: Could not reload .env file:", reloadResult.error.message);
    }
    
    return reloadResult;
}

module.exports = { loadEnvFile };
