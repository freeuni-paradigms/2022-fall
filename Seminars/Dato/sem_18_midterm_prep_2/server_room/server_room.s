// struct, offset, size
// cpu, _, 8
// id, 0, 4
// cores 4, 4

// serverRoom, _, 20
// model 0, 4
// node 4, 8
// next, 16, 4

SP = SP - 4 // make space for localScript variable

/**
SP + 12 servers
SP + 8 roomNumber
SP -> localScript
**/

// line 1
// roomNumber[*roomNumber] = 0;
R1 = M[SP + 8]; // roomNumber
R2 =.2 M[R1]; // *roomNumber
R2 = R2 * 2; // roomNumber + 2*roomNumber
R3 = R1 + R2;  // roomNumber[*roomNumber]
M[R3] =.2 0;

// line 2
// if (servers[2].node.id > 3)
R1 = SP + 12 // servers
R2 = 20*2 // &servers[2]
R3 = M[R1 + R2] // servers[2].node.id
BLE R1, 3, PC + 7*4

// line 3 (6 lines)
//    servers += ((struct cpu *) (servers->next[0].cores))->id;
// this line is correct according to the handout
// will add comments later
R1 = M[SP + 12];
R2 = M[R1 + 16];
R3 = M[R2 + 8];
R4 = R3 * 16
R5 = R1 + R4
M[SP + 12] = R5

// line 4
// bootstrapScript localScript = GetSetupScript(servers[0].model);
R1 = SP + 12; // servers[0].model (which is same ase &servers)
SP = SP – 4; // GetSetupScript arguments
M[SP] = R1; // model
CALL <GetSetupScript>
SP = SP + 4 // free GetSetupScript arguments
M[SP] = RV // assign to localscript

// line 5
//  return SetupServers((struct cpu *)&servers, localScript);
R1 = M[SP + 12] // servers
R2 = M[SP] // localScript
SP = SP - 8
M[SP] = R1 // script
M[SP + 4] = R1 // server
CALL <SetupServers>
SP = SP + 8; // free SetupServer arguments

// SetupServers result is already in RV
// return
SP = SP + 4 // free localScript
RET;