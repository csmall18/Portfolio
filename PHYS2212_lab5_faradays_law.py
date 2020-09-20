from vpython import *
#GlowScript 2.7 VPython
# Physical constants
u0over4pi = 1e-7
resistivity = 2.65e-8 # resistivity of aluminum, in ohm-meters
g = 9.81

# Geometry of the tube

############################
# Edit these lines
# STEP 1
L = 0.307 # Length of tube (m)
width = 0.01 # Width of foil (m)
inner_rad = 0.015 # Inner radius of tube (m)
############################

rad = width + inner_rad      # radius (center to outer surface)
# Numerical parameters for simulation
dy = 0.005      # vertical thickness of each tube segment
Nlength = round(L/dy) # total number of tube segments
gridstep = 0.001# distance between elements of flux surface
deltat = 0.001
dropStep = 0.001# distance used to calculate B gradient

# Initial conditions
t = 0

# Create the bar magnet
mass = 0.0241    # mass
m = 2.51           #    dipole moment magnitude (original: 3.098, recalculated to be closer to measured time: 2.51)
bar = cylinder(pos=vec(0,0.0,0), axis = vec(0,0.025,0), radius = 0.0065)
bar.m = m*bar.axis/mag(bar.axis)    # dipole points along magnet's axis
bar.v = vec(0,0,0)
mhat = bar.m/mag(bar.m)  

plot = graph(title='Velocity vs. Time', xtitle='Time (s)', ytitle='Velocity (m/s)')
poscurve = gcurve(color=color.black, width=2)

# Create tube as a series of rings stacked along the y direction.  The y axis is perpendicular to the plane of each ring.  The y axis passes
# through the center of each ring.
# This part of the code is already complete, don't alter it
tube = []
for i in range(Nlength):
    thisSegment = extrusion(path=[vec(0,-(i*dy),0),vec(0,-(1+i)*dy,0)], 
        shape=shapes.circle(radius = rad, thickness = width/rad))
    thisSegment.current = 0 # CW from above defined as positive
    thisSegment.flux = 0
    thisSegment.radius = rad-width
    thisSegment.R = resistivity*(2*pi*thisSegment.radius)/(width*dy)
    tube.append(thisSegment)

############################
# Edit these lines
# STEP 2
# (you may use your lab 3 code)
def dipoleB(mu, r): # cutoff=1e-5
    rhat = r/mag(r)
    rmag = mag(r)
    B = u0over4pi*(1/rmag**3)*((3*(dot(mu,rhat)*rhat) - mu))
    return B
############################


############################
# Edit these lines
# STEP 3
# Calculate dFlux/dt through ring due to falling magnet; see lecture 43
def calculateDFluxDtAnalytic(magnet, ring):
    num = ((3/2)*(4*pi*u0over4pi)*mag(magnet.m)*(magnet.pos.y-ring.pos.y)*mag(magnet.v)*(ring.radius)**2)
    den = ((ring.radius**2)+(magnet.pos.y-ring.pos.y)**2)**(5/2)
    dFdt = num/den
    return dFdt
############################
    

# Detects when the magnet enters the tube
entered = False
exited = False

# SIMULATION LOOP
while bar.pos.y >= -L:  # let the magnet drop out instead of stopping at -L
    rate(1600)   # Adjust until the simulation runs smoothly; bigger = faster
    bar.pos = bar.pos+(bar.v*deltat)
    t +=  deltat
    
    if not entered:
        if bar.pos.y <= tube[0].pos.y:
            enterTime = t
            entered = True
    
    if not exited:
        if bar.pos.y <= tube[-1].pos.y:
            exitTime = t
            exited = True
            
    ############################
    # Edit these lines
    # STEP 7.1
    # gravitational force on magnet
    F_g = vec(0,-mass*g,0)    # gravitational force
    # print("F_g: ", F_g)
    ############################
    
    # magnetic force from tube on magnet
    magF_on_magnet=0#MFS
    for ring in tube:
        #compute dflux/dT for ring due to falling magnet
        dFluxdt = calculateDFluxDtAnalytic(bar, ring)    
        # print("dFluxdt: ", dFluxdt)
        ############################
        # Edit these lines
        # Step 4
        # Calculate the current in the ring
        ring.current = dFluxdt/thisSegment.R
        ############################
        
        # color each ring according to current
        if ring.current > 0:
            ring.color = vec(1e-1*abs(ring.current)+0.3,0.3,0.3)
        else:
            ring.color = vec(0.3,0.3,1e-1*abs(ring.current)+0.3)
            
        ############################
        # Edit these lines
        # Steps 5, 6
        # SEE Chabay and Sherwood 4th edition, pg 830 and Lecture 43
        #"typical" location on ring w.r.t. magnet
        r_ring = vector(ring.radius,ring.pos.y-bar.pos.y,0) # keep this line
        #compute "typical" B field at ring...note B field assumed axisymmetric
        B_at_ring = dipoleB(bar.m, r_ring)
        # print("B at ring: ", B_at_ring)
        Bhat = norm(B_at_ring)
        sintheta = mag(cross(mhat,Bhat))
        # print("Current: ",thisSegment.current)
        magF_on_ring = abs(ring.current)*2*pi*ring.radius*sintheta*mag(B_at_ring) # F = ILB
        magF_on_magnet += magF_on_ring #Newton's 3rd Law used here, keep this line
        ############################
        
    # calculate force on magnet
    F_B = vector(0,magF_on_magnet,0)
    # print("F_B: ", F_B)
    ############################
    # Edit these lines
    # Step 7.2
    Fnet = F_g+F_B
    # print("Fnet: ", Fnet)
    ############################
    
    ############################
    # Edit these lines
    # Step 8
    bar.v += vector(0,(Fnet.y/mass)*deltat,0)
    # print("v: ", bar.v)
    bar.pos += vector(0,bar.v.y*deltat,0)
    ############################

    # Plot position vs. time
    poscurve.plot(t,bar.v.y)    
    
print('Time in tube: {:.3f} s'.format(exitTime - enterTime))
print("Measured average time: 2.02 s")