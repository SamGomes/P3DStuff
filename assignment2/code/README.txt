//////////////////////////////////////
//  Executing program Instructions  //
//////////////////////////////////////

1 - Open "Assignment2.sln" using Visual Studio 2013 or a more recent version.
2 - Press "Local Windows Debugger" button or the "F5" keyboard key.
3 - The following options can be changed using the global variables:
	a) "filePath": The file path for the NFF file to load.
	b) "draw_mode": Changes the display rate of pixels on the screen to point by point (0), line by line (1) or full frame (3).
	c) "MAX_DEPTH": Max number of reflections and refractions considered by each traced primary ray.
	d) "nSamples": The size N of a matrix NxN of rays casted for each pixel.
	e) "useDOF": If true, depth of field is used to render the scene using a sample size of nSamples.
	f) "thinLensParameters": The parameters lens radius, focus distance, view plane distance and zoom for the ThinLensCamera. 
		(Only used if useDOF is true)
	g) "useSoftShadows": If true, area lights are rendered in the scene using a sample size of nSamples.
	h) "mGridFactor": The M factor for the uniform acceleration grid, the higher value the higher the number of cells.
		If the M factor is 0, the grid will only have 1 cell.
4 - Enjoy the results!! :D