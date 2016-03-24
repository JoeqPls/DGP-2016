//=============================================================================


#include "ImplicitRBF.hh"


//== IMPLEMENTATION ==========================================================


ImplicitRBF::
	ImplicitRBF( const std::vector<Vec3f>& _points, 
	const std::vector<Vec3f>& _normals )
{
	//////////////////////////////////////////////////////////////////////
	// INSERT CODE:
	// 1) collect constraints (on-surface and off-surface)
	double epsilon = 0.01;
	
	centers_.clear();
	for(int i=0;i<_points.size();i++)
	{
		Vec3d point(_points[i]);
		centers_.push_back(point);
	}
	for(int i=0;i<_normals.size();i++)
	{
		Vec3d normal(_normals[i]);
		normal = centers_[i] + epsilon * normal;
		centers_.push_back(normal);
	}

	// 2) setup matrix
	int n = centers_.size();
	gmmMatrix M(n,n);
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			M(i,j) = kernel(centers_[i],centers_[j]);
		}
	}

	gmmVector b(n);
	for(int i=0;i<n;i++)
	{
		if(i < n/2) b[i]=0;
		else b[i] = epsilon;
	}
	
	// 3) solve linear system for weights_
	solve_linear_system(M,b,weights_);

	//////////////////////////////////////////////////////////////////////
}


//-----------------------------------------------------------------------------


void
ImplicitRBF::solve_linear_system( gmmMatrix& _M, 
																	gmmVector& _b, 
																	gmmVector& _x)
{
	// solve linear system by gmm's LU factorization
	unsigned int N = _b.size();
	_x.resize(N);
  std::vector< size_t >  ipvt(N);
  gmm::lu_factor( _M, ipvt );
  gmm::lu_solve( _M, ipvt, _x, _b );
}


//-----------------------------------------------------------------------------


double 
ImplicitRBF::operator()(const Vec3f& _p) const
{
  std::vector<Vec3d>::const_iterator  
    c_it(centers_.begin()),
    c_end(centers_.end());

  std::vector<double>::const_iterator   
    w_it(weights_.begin());

	const Vec3d p(_p);
  double f(0);

  for (; c_it!=c_end; ++c_it, ++w_it)
    f += *w_it * kernel(*c_it, p);

  return f;
}


//=============================================================================
