"""
Name: Alex Choi
Last Edited: April 2024

### Problem Description

This code solves a system of two ordinary differential equations (ODEs) that define the trajectory and velocity of a free-falling object with air resistance. The ODEs are based on:

1. Position equation: ∂x/∂t = v(t)
2. Velocity equation: ∂v/∂t = g - (c_d/m) * v^2

where:
- x(t) is the position,
- v(t) is the velocity,
- g is the gravitational constant,
- c_d is the drag coefficient, and
- m is the mass of the object.

The initial conditions are x(0) = 0 and v(0) = 0. Using the Runge-Kutta 4th order (RK4) scheme, the code numerically estimates the position and velocity of the object over time, factoring in air resistance.

"""
import numpy as np
error = 'error'

def solve_freefall_RK4(x0: float, v0: float, nt: int, dt: float, g: float, cd: float, m: float):
    """ 
    Applies the Runge − Kutta4 scheme in order to numerically solve the problem below from time t = 0 to some future point in time.

    Consider the initial value problem for a system of 2 ODE’s that define the trajectory and velocity of a free falling object, x,v respectively:
    ∂x/∂t = v(t)
    ∂v/∂t = g − (c_d/m)v^2
    Initial conditions: x(0) = 0, v(0) = 0

    :param x0: Initial position
    :param v0: Initial velocity
    :param nt: Number of time steps • float dt: Time step size
    :param g: Gravitational constant • float cd: Coefficient of drag
    :param cd: Coefficient of drag
    :param m: mass of the object

    :return x: the position x(t) of length nt at each point in time: t = 0, dt, 2dt, 3dt, .., nt ∗ dt, as estimated by the RK4 scheme
    :return v: the velocity(t) at each point in time, as estimated by the RK4 scheme
    """
    # first define two functions
    def dx_dt(v):
        return v
    def dv_dt(v):
        return g - (cd / m) * v**2
    
    # initialize two lists for return value x and v
    x = np.zeros(nt + 1, dtype = float) # positions at t = 0, ..., nt * dt
    v = np.zeros(nt + 1, dtype = float) # velocities at t = 0, ..., nt * dt

    # initial position, x0, and initial velocity, v0:
    x[0], v[0] = x0, v0

    # we have to compute x and v simultaneously:
    for i in range(nt): # have to run from dt to nt * dt
        # k1 for x and v where k1 = f(ti, vi)
        k1_x = dx_dt(v[i]) # be careful to use v, not x
        k1_v = dv_dt(v[i])

        # k2 for x and v where k2 = f(ti + dt/2, vi + k1 * dt/2)
        k2_input = v[i] + k1_v * dt / 2
        k2_x, k2_v = dx_dt(k2_input), dv_dt(k2_input)

        # k3 for x and v where k3 = f(ti + dt/2, vi + k2 * dt/2)
        k3_input = v[i] + k2_v * dt / 2
        k3_x, k3_v = dx_dt(k3_input), dv_dt(k3_input)

        # k4 for x and v where k4 = f(ti + dt/2, vi + k3 * dt)
        k4_input = v[i] + k3_v * dt
        k4_x, k4_v = dx_dt(k4_input), dv_dt(k4_input)

        # now compute x_i+1 and v_i+1
        # x_i+1 = xi + (k1 + 2k2 + 2k3 + k4) * dt / 6
        x[i + 1] = x[i] + (k1_x + 2 * k2_x + 2 * k3_x + k4_x) * dt / 6.0
        # v_i+1 = vi + (k1 + 2k2 + 2k3 + k4) * dt / 6
        v[i + 1] = v[i] + (k1_v + 2 * k2_v + 2 * k3_v + k4_v) * dt / 6.0

    # finally return the vectorsL
    return x, v