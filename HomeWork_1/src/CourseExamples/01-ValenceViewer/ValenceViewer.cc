//=============================================================================
//                                                
//   Code framework for the lecture
//
//   "Surface Representation and Geometric Modeling"
//
//   Mark Pauly, Mario Botsch, Balint Miklos, and Hao Li
//
//   Copyright (C) 2007 by  Applied Geometry Group and 
//							Computer Graphics Laboratory, ETH Zurich
//                                                                         
//-----------------------------------------------------------------------------
//                                                                            
//                                License                                     
//                                                                            
//   This program is free software; you can redistribute it and/or
//   modify it under the terms of the GNU General Public License
//   as published by the Free Software Foundation; either version 2
//   of the License, or (at your option) any later version.
//   
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License for more details.
//   
//   You should have received a copy of the GNU General Public License
//   along with this program; if not, write to the Free Software
//   Foundation, Inc., 51 Franklin Street, Fifth Floor, 
//   Boston, MA  02110-1301, USA.
//                                                                            
//=============================================================================
//=============================================================================
//
//  CLASS ValenceViewer - IMPLEMENTATION
//
//=============================================================================


//== INCLUDES =================================================================

#include "ValenceViewer.hh"
#include "Myfunctions.h"
#include <vector>
#include <float.h>



//== IMPLEMENTATION ========================================================== 


ValenceViewer::
ValenceViewer(const char* _title, int _width, int _height)
  : MeshViewer(_title, _width, _height)
{ 
  mesh_.request_vertex_colors();

  add_draw_mode("Vertex Valences");

}


//-----------------------------------------------------------------------------


ValenceViewer::
~ValenceViewer()
{
}

//-----------------------------------------------------------------------------

bool
ValenceViewer::
open_mesh(const char* _filename)
{
  // load mesh
  if (MeshViewer::open_mesh(_filename))
  {
    // compute vertex valence and color coding
    calc_valences();
    color_coding();

    glutPostRedisplay();
    return true;
  }
  return false;
}


//-----------------------------------------------------------------------------


void 
ValenceViewer::
calc_valences()
{
  // EXERCISE 1.2 /////////////////////////////////////////////////////////////
  // Compute valence of every vertex of "mesh_" and store them in each vertex
  // using for example custom attributes via dynamic customization
  // (hint: use the Mesh::VertexIter iterator)

	Mesh::VertexIter v_iter, v_begin, v_end;

	v_begin = mesh_.vertices_begin();
	v_end = mesh_.vertices_end();

	int vertexValence;
	vertex_valences_.clear();

	OpenMesh::VPropHandleT<int> Valence;  
	 mesh_.add_property(Valence,"Valence"); 
	
	 for(v_iter = v_begin; v_iter != v_end; ++v_iter)
	{
		vertexValence = 0;
		Mesh::VertexOHalfedgeIter voh_Iter;
		for (voh_Iter = mesh_.voh_iter(v_iter); voh_Iter; ++voh_Iter) 
		{
			vertexValence++;
		}
		
		vertex_valences_.push_back(vertexValence);

		mesh_.property(Valence,v_iter) = vertexValence;

//		std::cout <<mesh_.property(Valence,v_iter)<<std::endl; 
	}
	 
//	std::cout<< "Max valence:" << getMax(vertex_valences_) << std::endl; 
//	std::cout<< "Min valence:" << getMin(vertex_valences_) << std::endl;
  /////////////////////////////////////////////////////////////////////////////
}


//-----------------------------------------------------------------------------


void 
ValenceViewer::
color_coding()
{
  // EXERCISE 1.3 /////////////////////////////////////////////////////////////
  // Implement a color visualization of your choice that shows the valence of
  // veach ertex of "mesh_". 
  // (hint: use Mesh::Color color type)
    
	Mesh::VertexIter v_iter, v_begin, v_end;

	v_begin = mesh_.vertices_begin();
	v_end = mesh_.vertices_end();

	int valenceMax = getMax(vertex_valences_);
	int valenceMin = getMin(vertex_valences_);

/*	Colorization Method:
	'seperatorValence' is the valence that corresponded vertexs' number is the max
	so,

	valence = minValence       , paint Red
	(min, sep)				   , paint Yellow
	valence = seperatorValence , paint Green
	(sep, max)				   , paint Cyan-Blue
	valence = maxValence       , paint Blue    */
	

	int seperatorValence = MAX;  
	int vertexNumber  = -1;
	for (int i=valenceMin;i<=valenceMax;i++)
	{
		int c_number = countNumber(vertex_valences_,i);

		if (c_number > vertexNumber)
		{
			vertexNumber = c_number;
			seperatorValence = i;
		}	
	}

	int maxDiff = valenceMax - seperatorValence;
	int minDiff = valenceMin - seperatorValence;

	int vertexValence = 0;
	OpenMesh::VPropHandleT<int> vPH_T;  

	for(v_iter = v_begin; v_iter != v_end; ++v_iter)
	{
		mesh_.get_property_handle(vPH_T,"Valence");  
		vertexValence = mesh_.property(vPH_T,v_iter.handle());
		int diffValence = vertexValence - seperatorValence;
		int r = 0,g = 0,b = 0;

		if (diffValence == minDiff)
		{
			r = 255;
		}
		else if (diffValence < 0)
		{
			r = 255;
			g = 255;	
		}
		else if (diffValence == 0)
		{
			g = 255;
		}
		else if (diffValence < maxDiff)
		{
			b = 255;
			g = 255;
		}
		else
			b = 255;
			
		mesh_.set_color(v_iter.handle(),Mesh::Color(r,g,b)); 
	
	}

  /////////////////////////////////////////////////////////////////////////////
}


//-----------------------------------------------------------------------------


void 
ValenceViewer::
draw(const std::string& _draw_mode)
{

  if (indices_.empty())
  {
    MeshViewer::draw(_draw_mode);
    return;
  }

  if (_draw_mode == "Vertex Valences")
  {

	  glDisable(GL_LIGHTING);
	  glShadeModel(GL_SMOOTH);
	  glEnableClientState(GL_VERTEX_ARRAY);
	  glEnableClientState(GL_NORMAL_ARRAY);
	  glEnableClientState(GL_COLOR_ARRAY);
	  GL::glVertexPointer(mesh_.points());
	  GL::glNormalPointer(mesh_.vertex_normals());
	  GL::glColorPointer(mesh_.vertex_colors());
	  glDepthRange(0.01, 1.0);
	  glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, &indices_[0]);
	  glDisableClientState(GL_VERTEX_ARRAY);
	  glDisableClientState(GL_NORMAL_ARRAY);
	  glDisableClientState(GL_COLOR_ARRAY);
	  glColor3f(0.1, 0.1, 0.1);
	  glEnableClientState(GL_VERTEX_ARRAY);
	  GL::glVertexPointer(mesh_.points());
	  glDrawBuffer(GL_BACK);
	  glDepthRange(0.0, 1.0);
	  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	  glDepthFunc(GL_LEQUAL);
	  glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, &indices_[0]);
	  glDisableClientState(GL_VERTEX_ARRAY);
	  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	  glDepthFunc(GL_LESS);
  }

  else MeshViewer::draw(_draw_mode);
}


//=============================================================================
