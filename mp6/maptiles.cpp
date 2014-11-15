/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */
	 			
#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

MosaicCanvas * mapTiles(SourceImage const & theSource, vector<TileImage> const & theTiles)
{
    /**
     * @todo Implement this function!
     */
 	
	MosaicCanvas * scene= new MosaicCanvas(theSource.getRows(),theSource.getColumns());
	
	vector< Point<3> > puppy;

	map<RGBAPixel,TileImage> Map;
	

	int m=0;
	while(m<theTiles.size())
	{
		TileImage tile=theTiles[m];
		RGBAPixel average= tile.getAverageColor();
		Point<3> tile_pixel (average.red, average.green, average.blue);
		pair< RGBAPixel, TileImage > mapTile(average, tile);
        	puppy.push_back(tile_pixel);
    		Map.insert(mapTile);
		m++;	
	}	

	KDTree<3> tree(puppy);
		
	for(int i=0;i<theSource.getRows();i=i++)
		for(int j=0;j<theSource.getColumns();j++)
		{
			RGBAPixel avg= theSource.getRegionColor(i,j);
			Point<3> tile_pixel(avg.red,avg.green,avg.blue);
			Point<3> inception = tree.findNearestNeighbor(tile_pixel);
    	  		RGBAPixel inception_avg(inception[0], inception[1], inception[2]);
      			map< RGBAPixel, TileImage >::iterator it = Map.find(inception_avg);
      			TileImage tile = it->second;
      			scene->setTile(i, j, tile);	
		}

	return scene;

}