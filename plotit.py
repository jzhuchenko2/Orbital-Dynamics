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

x_bh = bh_radius * np.outer(np.cos(u), np.sin(v))
y_bh = bh_radius * np.outer(np.sin(u), np.sin(v))
z_bh = bh_radius * np.outer(np.ones(np.size(u)), np.cos(v))
ax.plot_surface(x_bh, y_bh, z_bh, color=bh_color, alpha=bh_alpha)

# Initialize spacecraft plot
line, = ax.plot([], [], [], label='Spacecraft Path', color='blue', linestyle='-', linewidth=2)
point, = ax.plot([], [], [], [], marker='o', markersize=10, color='blue')

# Set plot labels and title
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
ax.set_title('Real-time Spacecraft Trajectory around Black Hole')

# Set equal aspect ratio
ax.set_box_aspect([1, 1, 1])

# Set initial view angle
ax.view_init(elev=30, azim=-45)

def update(frame):
    t = time[frame]
    x_smooth, y_smooth, z_smooth = splev(u_new, tck)

    # Update spacecraft trajectory
    line.set_data(x_smooth[:frame+1], y_smooth[:frame+1])
    line.set_3d_properties(z_smooth[:frame+1])
