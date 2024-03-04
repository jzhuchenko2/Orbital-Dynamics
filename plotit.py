import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from scipy.interpolate import splprep, splev
from matplotlib.animation import FuncAnimation

# Read position data from file
data = np.loadtxt('output.dat')

# Extract time and position coordinates
time = data[:, 0]
x = data[:, 1]
y = data[:, 2]
z = data[:, 3]

#we're getting somewhere now. hold on 
# Smooth the spacecraft trajectory using spline interpolation
tck, u = splprep([x, y, z], s=0)

ax = fig.add_subplot(111, projection='3d')
