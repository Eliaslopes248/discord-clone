
function test(num){
    return num ==0;
}

describe("Testing authentication system", ()=>{

    it("testing example func", ()=>{
        expect(test(2)).toBe(false);
    });

});