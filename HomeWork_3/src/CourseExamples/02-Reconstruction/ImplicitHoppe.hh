//=============================================================================


#ifndef HOPPE_HH
#define HOPPE_HH


//=============================================================================


#include <OpenMesh/Core/Math/VectorT.hh>
#include <vector>
#include <float.h>


//=============================================================================


class ImplicitHoppe
{
public:

	typedef OpenMesh::Vec3f Vec3f;

	
  // fit RBF to given constraints
  ImplicitHoppe( const std::vector<Vec3f>& _points, 
								 const std::vector<Vec3f>& _normals )
		: points_(_points), normals_(_normals)
	{}


  // evaluate implicit at position _p
  float operator()(const Vec3f& _p) const
	{
		float dist(0);
		//////////////////////////////////////////////////////////////////////
		// INSERT CODE:
		std::vector<Vec3f>::const_iterator 
			p_it(points_.begin()),
			p_end(points_.end()),
			n_it(normals_.begin()),
			n_end(normals_.end());

		// 1) find closest sample point
		float minDis = (float) 1e6;
		int index = 0;
		Vec3f p_closest,n_closest;

		for (; p_it != p_end && n_it != n_end; ++p_it,++n_it)
		{
			float dis = (_p - *p_it).length();
			if (dis < minDis)
			{
				minDis = dis;
				p_closest = *p_it;
				n_closest = *n_it;
			}
		}

		// 2) compute distance to its plane
		float d_upper,d_lower;
		Vec3f v_delta = _p - p_closest;
		d_upper = v_delta | n_closest;
		d_lower = n_closest.length();
		dist = d_upper/d_lower;
		
		//////////////////////////////////////////////////////////////////////
		return dist;
	}

  

private:

	const std::vector<Vec3f>&  points_;
	const std::vector<Vec3f>&  normals_;
};


//=============================================================================
#endif // RBF_HH defined
//=============================================================================

