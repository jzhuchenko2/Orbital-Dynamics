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
tck, u = splprep([x, y, z], s=0)
u_new = np.linspace(0, 1, 1000)

# Create figure and 3D axis
fig = plt.figure(figsize=(10, 8))

ax = fig.add_subplot(111, projection='3d')


# Plot black hole
bh_radius = 1.0  # Radius of the black hole
bh_color = 'black'  # Color of the black hole
bh_alpha = 0.5  # Transparency of the black hole
u = np.linspace(0, 2 * np.pi, 100)
v = np.linspace(0, np.pi, 100)
