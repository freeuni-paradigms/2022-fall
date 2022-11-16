// we recommend writing basic offsets here
// variables, struct members, struct sizes

// struct, offset, size
// cpu, _, 8
// id, 0, 4
// cores 4, 4

// serverRoom, _, 16
// model 0, 4
// node 4, 8
// next, 12, 4

/**
SP + 12 ->servers
SP + 8 -> roomNumber
SP -> localScript
**/

// ------------------------------------

SP = SP - 4 // make space for localScript variable

// line 1
// roomNumber[*roomNumber] = 0;
R1 = M[SP + 8]; // roomNumber / &roomNumber[0]
R2 =.2 M[R1]; // *roomNumber / roomNumber[0]
R3 = R2 * 2; // offset from roomNumber
R4 = R1 + R3;  // roomNumber + offset / & roomNumber[*roomNumber]
M[R4] =.2 0; // write 0 to roomNumber[*roomNumber]


// line 2
// if (servers[2].node.id > 3)
R1 = M[SP + 12] // servers / &servers[0]
R2 = 16 * 2 // offset
R3 = R1 + R2 // servers + offset / &servers[2] 
R4 = R3 + 4 // &servers[2].node.id / &servers[2].node 
R5 = M[R4] // servers[2].node.id
BLE R5, 3, PC + 40


// line 3
// servers += ((struct cpu *) (servers->next[0].cores))->id;
R1 = M[SP + 12] // servers / &servers[0]
R2 = R1 + 12  // &servers->next / &servers[0].next
R3 = M[R2] // servers->next / &servers->next[0]
R4 = R3 + 4 // servers->next[0].cores / &servers->next[0].cores[0]
// cores ჰო შორტების მასივია, cpu-ების მასივად რომ გავიაზროთ და მაგის მენოლეს აიდი ამოვიღოთ იქნება ეს ხაზი.
R5 = M[R4] // ((struct cpu *) (servers->next[0].cores))->id / ((struct cpu *) (servers->next[0].cores))[0].id
R6 = M[SP + 12] // servers
R7 = R5 * 16 // offset (pointer arithmetic with value of R5)
R8 = R6 + R7 // servers + offset
M[SP + 12] = R8 // update servers value (because of "+=")


// line 4
// bootstrapScript localScript = GetSetupScript(servers[0].model);
R1 = M[SP + 12] // servers / &servers[0] / &servers[0].model
R2 = M[R1] // servers[0].model
SP = SP - 4 // make space for GetSetupScript arguments
M[SP] = R2 // write servers[0].model as argument for GetSetupScript
CALL <GetSetupScript>
SP = SP + 4 // free space of GetSetupScript arguments
M[SP] = RV // write return value in localScript variable
  

// line 5
// return SetupServers((struct cpu *)&servers, localScript);
R1 = SP + 12 // &servers / (struct cpu *)&servers
R2 = M[SP] // localScript
SP = SP - 8
M[SP] = R1;
M[SP + 4] = R2;
CALL <SetupServer>
SP = SP + 8

// SetupServers result is already in RV
SP = SP + 4 // free localScript
RET;
