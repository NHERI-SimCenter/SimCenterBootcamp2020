import geopandas as gpd
import matplotlib.pyplot as plt 
from mpl_toolkits.axes_grid1 import make_axes_locatable 

# Reading the world shapefile 
world_data = gpd.read_file(r'D:\GeoDelta\Introduction to Geopandas_Basics\Visualizing Geographical Data\world.shp')
world_data = world_data[['NAME', 'geometry']]

# Calculating the area of each country 
world_data['area'] = world_data.area

# Removing Antarctica from GeoPandas GeoDataframe
world_data = world_data[world_data['NAME'] != 'Antarctica']
world_data.plot()

# Changing the projection
current_crs = world_data.crs   
world_data.to_crs(epsg = 3857, inplace = True)
world_data.plot(column = 'NAME', cmap = 'hsv')

# Re-calculate the areas in Sq. Km.
world_data['area'] = world_data.area/1000000

# Adding a legend 
world_data.plot(column = 'area' , cmap = 'hsv' , legend = True, 
                legend_kwds = {'label': "Area of the country (Sq. Km.)"}, figsize = (7,7))

# Resizing the legend 
fig, ax = plt.subplots(figsize = (10,10))
divider = make_axes_locatable(ax)
cax = divider.append_axes("right", size = "7%", pad = 0.1)
world_data.plot(column = 'NAME' , cmap = 'hsv' , legend = None, 
                legend_kwds = {'label': "Area of the country (Sq. Km.)"},
                ax = ax, cax = cax)