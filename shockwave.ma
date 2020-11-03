[top]
components : shockwave  incomingVehicle1@MyGenerator incomingVehicle2@MyGenerator
link : out@incomingVehicle1 inputVehicles1@shockwave
link : out@incomingVehicle2 inputVehicles2@shockwave

[shockwave]
type : cell
dim : (30,2)
delay : transport
defaultDelayTime  : 1
border : nowrapped
neighbors : shockwave(-1,-1) shockwave(-1,0) shockwave(-1,1) 
neighbors : shockwave(0,-1)  shockwave(0,0) shockwave(0,1)
neighbors : shockwave(1,-1)  shockwave(1,0) shockwave(1,1)
in : inputVehicles1 inputVehicles2
link : inputVehicles1 in@shockwave(29,0)
link : inputVehicles2 in@shockwave(29,1)
zone : outVehicles { (0,0)..(0,1) }

InitialValue : 0
InitialCellsValue : vehicle.val

portInTransition : in@shockwave(29,0)  setVehicle1
portInTransition : in@shockwave(29,1)  setVehicle2
localtransition : traffic-rule


# NOTE: We use 1 to represent cars that in the left lane; and 2 for
# Represent cars that in the right lane; 0 means no cars in the cell

[traffic-rule]
rule : 0  1 { (0,0) = 1 and (-1,0) = 0 }
rule : 1  1 { (0,0) = 0 and (1,0) = 1 }
rule : 0  1  { (0,0) = 2 and (-1,0) = 0 }
rule : 2  1  { (0,0) = 0 and (1,0) = 2 }
rule : 0  1  { (0,0) = 1 and (-1,0) = 1 and (0,1) = 0 and (-1,1) = 0 }
rule : 2  1  { (0,0) = 0 and (1,0) = 0 and (1,-1) = 1 and (0,-1) = 1 }
rule : 0  1  { (0,0) = 2 and (-1,0) = 2 and (0,-1) = 0 and (-1,-1) = 0 }
rule : 1  1  { (0,0) = 0 and (1,0) = 0 and (1,1) = 2 and (0,1) = 2 }
rule : { (0,0) }  1  { t }

[setVehicle1]
rule : { portValue(in) } 0 { t }

[setVehicle2]
rule : { portValue(in) } 0 { t }

[incomingVehicle1]
distribution : exponential    
mean : 1   
initial : 1    
increment : 0

[incomingVehicle2]
distribution : exponential    
mean : 1    
initial : 2
increment : 0

[outVehicles]
rule : 0 10 { t }