import requests

#Let's request the tall buildings information
response = requests.get("https://data.sfgov.org/resource/5kya-mfst.json")

#Let's check the response is OK (return code 200)
if(response.status_code == 200):
    #We will convert the response to json 
    tallBuildings = response.json()
    
    #we will read the first building in the response and print some information
    building = tallBuildings[0]
    print("Building Name", ["name"])
    print("\tOccupancy: ", building["occupancy"])
    print("\tAddress: ", building["address"])

#Excercise 1: Print to the screen the list of buildings 
#including relevant information about the building like structure type
#occupancy, number of stories, , total area.


#Excercise 2: Write the data from excercise 1 into a csv text file including latitude and longitude


#Exercise 3: Can we get PGA from USGS API for each building and include it in the output file
