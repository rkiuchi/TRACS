/*
 * @ Copyright 2014-2017 CERN and Instituto de Fisica de Cantabria - Universidad de Cantabria. All rigths not expressly granted are reserved [tracs.ssd@cern.ch]
 * This file is part of TRACS.
 *
 * TRACS is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation,
 * either version 3 of the Licence.
 *
 * TRACS is distributed in the hope that it will be useful , but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License along with TRACS. If not, see <http://www.gnu.org/licenses/>
 */

#include <cmath>
#include <array>

/*
 * SOURCE TERM
 *
 * This class contains the source term for the poisson equation
 * Space charge distribution is parametrized here.
 *
 *
 */
 class Source : public Expression
 {
 public:

	 //Declaration and default values. They will taken from steering file.
	// Concentration in transition and extremal points
	double y0 = -25.; // Neff(z0)
	double y1 = 0.02; // Neff(z1)
	double y2 = y1+y1*10; // Neff(z2)
	double y3 = 33; // Neff(z3)

	// Define diferent zones in depth
	double z0 = 0.;
	double z1 = 120.;
	double z2 = 220.;
	double z3 = 300.;
	std::string NeffApproach = "Triconstant";


    // For LGAD : Base of the effective doping level
    double _lgad_bulk_base_neff;
    double _coeff_gauss;

    double _peak_height;
    double _peak_position;
    double _gauss_sigma;
    double _f_poisson;
    
    
	void eval(Array<double>& values, const Array<double>& x) const
	{
		if (NeffApproach == "Triconstant") 
		{
			/*
			 * 3 ZONE constant space distribution
			 *
			 * We define here a Neff distribution consisting in 3 different zones
			 * each zone is defined as a constant within the given region.
			 * It uses all but the last parameter (y3 = Neff(z3)). It takes zX 
			 * values as boundaries of the zones and the three first yX as the 
			 * value of Neff in each region
			 *
			 * Even though a function like this is generally not continuous, we 
			 * add the hyperbolic tangent bridges to ensure not only continuity 
			 * but also derivability.
			 *
			 */
			double neff_1 = y0;
			double neff_2 = y1;
			double neff_3 = y2;

			// For continuity and smoothness purposes
			double bridge_1 = tanh(1000*(x[1]-z0)) - tanh(1000*(x[1]-z1));
			double bridge_2 = tanh(1000*(x[1]-z1)) - tanh(1000*(x[1]-z2));
			double bridge_3 = tanh(1000*(x[1]-z2)) - tanh(1000*(x[1]-z3));

			double neff = 0.5*((neff_1*bridge_1)+(neff_2*bridge_2)+(neff_3*bridge_3));
			values[0] = neff*0.00152132;
		}
		else if (NeffApproach == "Linear") 
		{
			/*
			 * 1 ZONE approximatin
			 *
			 * First aproximation to the after-irradiation space charge distribution
			 * Consists on a simple straight line defined by the points (z0, y0) and 
			 * (z3, y3) and neglects the rest of the values.
			 *
			 */

			double neff = ((y0-y3)/(z0-z3))*(x[1]-z0) + y0;
			values[0] = neff*0.00152132;
		}
        else if ( NeffApproach == "AvalancheMode" )
        {
            constexpr auto elementary_charge = 1.60217662e-19;    // [ C ]
            constexpr auto vacuum_permittivity = 8.85418782e-12;  // [ F/m ]
            constexpr auto relative_permittivity_silicon = 11.9;  // no unit.
            constexpr auto permittivity = vacuum_permittivity * relative_permittivity_silicon;  // [ F/m ]
            auto poisson_term =  ((std::signbit(_f_poisson)== false) ? +1.0 : -1.0) * ( elementary_charge * _peak_height * 1e6 / permittivity );  // [ V/m/m ]
            auto poisson_term_unit_microm = poisson_term * 1e-12;  // [ V/um/um ]
            
            auto gauss_term = poisson_term_unit_microm * std::exp(- std::pow((_peak_position - x[1]), 2.0)/(2*std::pow(_gauss_sigma, 2.0))) ;
            auto base_term = _f_poisson ;
            
            values[0] = base_term + gauss_term;
        }
		else 
		{
			/*
			 * 3 ZONE space distribution
			 *
			 * It consists in 3 different straight lines corresponding to 3 different
			 * charge distributions. It uses all 8 parameters to compute the Neff.
			 *
			 * Continuity is assumed as straight lines have common points, continuity 
			 * is ensured by the hyperbolic tangent bridges
			 */
			double neff_1 = ((y0-y1)/(z0-z1))*(x[1]-z0) + y0;
			double neff_2 = ((y1-y2)/(z1-z2))*(x[1]-z1) + y1;
			double neff_3 = ((y2-y3)/(z2-z3))*(x[1]-z2) + y2;

			// For continuity and smoothness purposes
			double bridge_1 = tanh(1000*(x[1]-z0)) - tanh(1000*(x[1]-z1));
			double bridge_2 = tanh(1000*(x[1]-z1)) - tanh(1000*(x[1]-z2));
			double bridge_3 = tanh(1000*(x[1]-z2)) - tanh(1000*(x[1]-z3));

			double neff = 0.5*((neff_1*bridge_1)+(neff_2*bridge_2)+(neff_3*bridge_3));
			values[0] = neff*0.00152132;

		}
		// Fix units from the PdC version


	}

    std::string get_NeffApproach() const
    {
        return NeffApproach;
    }        
	void set_NeffApproach(std::string Neff_type)
	{
		NeffApproach = Neff_type;
	}

    void set_avalanche_doping_param( const std::array<double, 3>& param )
    {
        _peak_height    = param[0];
        _peak_position = param[1];
        _gauss_sigma  = param[2];
    }
    void set_bulk_doping_param( const double& param )
    {
        _f_poisson = param;
    }
    
	void set_y0(double newValue)
	{
		y0 = newValue;
	}

	void set_y1(double newValue)
	{
		y1 = newValue;
	}

	void set_y2(double newValue)
	{
		y2 = newValue;
	}

	void set_y3(double newValue)
	{
		y3 = newValue;
	}

	void set_z0(double newValue)
	{
		z0 = newValue;
	}

	void set_z1(double newValue)
	{
		z1 = newValue;
	}

	void set_z2(double newValue)
	{
		z2 = newValue;
	}

	void set_z3(double newValue)
	{
		z3 = newValue;
	}

 };
