
/**
 * @author Elias Lopes
 * @Date   10/24/2025
 * @description 
 *  This file contains permission and authorization utilities
 *  for API route protection and user access control
 * 
 *  - CommonJS module format
 *  - Reusable authorization functions
 *  - Standard response formatting using RC_CODE system
 */

const { RC_CODES } = require('./errors.js');

//------------------------------------------------------------------
// Standard response formatting
//------------------------------------------------------------------

/**
 * Creates a standardized response object for API endpoints
 * @param {number} status - HTTP status code
 * @param {string} message - Response message
 * @returns {object} Standardized response object
 * @deprecated Use RC_CODES instead for better error handling
 */
function STANDARD_RESPONSE(status, message) {
    return {
        status: status,
        message: message
    };
}

/**
 * Creates a standardized response using RC_CODE system
 * @param {RC} rcCode - RC_CODE object from errors.js
 * @param {object} additionalData - Additional data to include in response
 * @returns {object} Standardized response object with RC_CODE structure
 */
function RC_RESPONSE(rcCode, additionalData = {}) {
    return {
        ...rcCode.HTTP_RC(rcCode.CODE),
        ...additionalData
    };
}

//---------------------------------------------------------------
module.exports = { RC_RESPONSE, RC_CODES };