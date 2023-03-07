from vpython import *
#GlowScript 2.7 VPython
from __future__ import division
from visual import *
scene.width = 1024
scene.height = 768
scene.x = scene.y = 0

# Constants
oofpez = 9e9
L = 9
Q = 3e-10
N = 25
scalefactor = 1
dz = L/N
dQ = Q/N
R = 0.5


# List of charges
list_of_charges = []
z = -L/2 + dz/2
while z < L/2:
    list_of_charges.append(sphere(pos=vector(0,0,z), radius=0.1, color=color.green))
    z = z+dz
print(len(list_of_charges))     # print number of items in the list


# List of arrows; tail of each arrow is at an observation location
dzz = ((10/8)*L)/10
list_of_arrows = []
for z in arange(-5*L/8, 5*L/8+0.001, dzz):
    for theta in arange(0,2*pi, pi/4):
        list_of_arrows.append(arrow(pos=vector(R*cos(theta), R*sin(theta),z),
                                    axis=vector(0,1,0)))

      
###############################################################
###############################################################
for n in [1,2,3,4,5]:
    list_of_arrows.append(arrow(pos = vector(n*(R/2),0,0),axis = vector(0,1,0)))
# Electric field calculation
# You need to complete this block of statements

for thisarrow in (list_of_arrows):      # take arrows one at a time
    rate(10)
   
    # Add statements to do the following things
    # (a) set Enet (the field at tail of thisarrow) to a zero vector here
    Enet= vector(0,0,0)
    for q in list_of_charges:
        r = thisarrow.pos - q.pos
        rmag = sqrt(r.x**2+r.y**2+r.z**2)
        rhat = r/rmag
        E = (dQ*oofpez)*(1/rmag**2)*rhat
        Enet = Enet + E
        thisarrow.axis = Enet*scalefactor          

    # (b) add indented statement to loop over list of charges
    
         
        # (c) add necessary program statements to calculate dE,
        # the field due to the current charge, at the observation
        # location (tail of arrow)
        
        # (d) add dE to Enet at this observation location
        
        # (e) uncomment to display Enet (multiply by scalefactor)
        #thisarrow.axis = Enet*scalefactor

    # Uncomment after calculating and displaying the electric field
    #thisarrow.color = color.magenta
    print("Enet is",mag(Enet))
print("done")
