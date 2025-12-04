

//----------------------------------------------------
// Implement test request to server
//----------------------------------------------------
async function registerUser(credentials)
{
    // make request to server 
    const response = await fetch("http://localhost:8000/auth/register", {
        method: "POST",
        headers: {"content-type" : "application/json"},
        body: { credentials: credentials }
    });

    // parse response
    const data = await response.json();

    // return response status
    return data.status;
}

//----------------------------------------------------
// Implement unit test
//----------------------------------------------------

describe("Testing authentication endpoints", ()=>{
    // give weak password
    it("Attempt to register with weak password", async ()=>{

        const credentials = {
            first_name: "unit test name",
            last_name:  "unit test name",
            username:   "unit test username",
            password:   "unit_password123",
        };

        expect(await registerUser(credentials)).toBe(400);
    });
});