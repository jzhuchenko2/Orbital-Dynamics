import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from scipy.interpolate import splprep, splev
from matplotlib.animation import FuncAnimation

# Read position data from file
data = np.loadtxt('output.dat')



#we're getting somewhere now. hold on 
