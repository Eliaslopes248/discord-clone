/**
 * auth related endpoints
 */

const {RC_CODES, RC_RESPONSE} = require("../utils/endpoint_helpers.js");
const express                 = require("express");
const router                  = express.Router();
const { MySQLConnector }      = require("../utils/sql_wrapper.js");
const { randomUUID }          = require("crypto");
const bcrypt                 = require("bcrypt")


// create mysql connection client (null for now to save memory)
let sqlConnection           = null;

async function getSqlClient()
{
    if (!sqlConnection){
        sqlConnection = new MySQLConnector(null, null, null, "discord_main");
        await sqlConnection._connectionPromise;
        return sqlConnection;
    }
    return sqlConnection;
}

//-----------------------------------------------------------------

async function attemptLogin(req, res, next)
{

}

async function userIsUnique(username=null)
{
    if (!username)
        return false;

    // check users table if the user exists already
    const con = await getSqlClient();

    // get results - use parameterized query to prevent SQL injection
    // Only check username for uniqueness (not password)
    const sql = `SELECT * FROM users WHERE username = ?`;
    const con_actual = await con._ensureConnection();
    const [result] = await con_actual.query(sql, [username]);

    if (!result)
        return false;

    // returns true if no results found (username is unique)
    return result.length == 0; 
}

// creates a hashed password for security
async function hashPassword(password)
{
    if (!password) return null;

    const saltRounds = 10;
    const hashed = await bcrypt.hash(password, saltRounds);
    return hashed;
}

// compares hashed password with the plain one
async function verifyPassword(plainPassword, hashedPassword) {
    const match = await bcrypt.compare(plainPassword, hashedPassword);
    return match;
}

// ensures username is acceptable


// ensures password is acceptable
function acceptablePassword(password)
{
    if (!password || password.length < 8) return false;

    // tests for different characters
    const number_test = /[0-9]/;
    const upper_case_test = /[A-Z]/;
    const lower_case_test = /[a-z]/;
    const special_char_test = /[!@#$%&*]/;

    // makes sure all tests pass
    return (
        password && 
        upper_case_test.test(password) &&
        lower_case_test.test(password) &&
        number_test.test(password)     &&
        special_char_test.test(password)
    );
}


async function attemptRegister(req, res, next)
{
    try {
        console.log("Registration request body:", JSON.stringify(req.body, null, 2));
        // get registration info from request
        const {credentials} = req.body;

        if (!credentials || !credentials.first_name || !credentials.last_name ||
            !credentials.username || !credentials.password
        ){
            return res.json(RC_RESPONSE(RC_CODES.BAD_REQUEST));
        }

        // make sure password is correct (check this first, no DB needed)
        if (!acceptablePassword(credentials.password)){
            console.error("Password is not acceptable");
            return res.json(RC_RESPONSE(RC_CODES.BAD_REQUEST));
        }

        // check if user is unique (only check username)
        const unique = await userIsUnique(credentials.username);

        if (!unique)
        {
            // user already exists -> reject request
            return res.json(RC_RESPONSE(RC_CODES.BAD_REQUEST));
        };

        // hash the password
        const hashed_password = await hashPassword(credentials.password);

        
        // add the user to the user table
        const con = await getSqlClient();

        // insert command - fixed function call syntax
        const result = await con.insertIntoTable(
            "users",
            ["user_id", "first_name", "last_name", "username", "password"],
            [[
                randomUUID(), 
                credentials.first_name, 
                credentials.last_name, 
                credentials.username, 
                hashed_password
            ]]
        );

        if(!result)
        {
            console.error("Error when trying to add to table:", result);
            return res.json(RC_RESPONSE(RC_CODES.SERVER_ERROR));
        }
        console.log("Results:", result);

        // add result to req packet
        req.user = result;

        // advance to next middleware
        return next();
    } catch (error) {
        console.error("Error in attemptRegister:", error);
        return res.json(RC_RESPONSE(RC_CODES.SERVER_ERROR));
    }
}


async function verifyJwt(token)
{

}

async function createdCustomJwt(payload)
{

}



//-----------------------------------------------------------------
router.post("/auth/login", attemptLogin,  (req, res)=>{

});

router.post("/auth/register", attemptRegister,  (req, res)=>{
    return res.json(RC_RESPONSE(
        RC_CODES.SUCCESS, {
        user: req.user
    }));
});




//-----------------------------------------------------------------
module.exports = router







//-----------------------------------------------------------------