% MEX_FNFT_NSEV_INVERSE Fast inverse nonlinear Fourier transform for the
% nonlinear Schroedinger equation with vanishing boundaries.
%
%   q = MEX_FNFT_NSEV(contspec, T, D, XI, kappa);
%   q = MEX_FNFT_NSEV(contspec, T, D, XI, kappa, OPTIONAL INPUTS);
%
% DESCRIPTION
%   Provides an interface to the C routine fnft_nsev_inverse.
%
% INPUTS
%   contspec        Complex row vector of length M>D, contains the samples
%                   of the reflection coefficient on an equidistant grid
%                   with end points given by XI below
%   T               Real 1x2 vector, contains the location of the first and
%                   the last sample in q
%   D               Real scalar, number of time domain samples; must be a
%                   positive power of two
%   XI              Real 1x2 vector, contains the location of the first and
%                   the last sample in contspec; must be computed with
%                   MEX_FNFT_NSEV_INVERSE_XI
%   kappa           +1.0 or -1.0
%
% OPTIONAL INPUTS
%   It is possible to provide additional inputs. These come either in the
%   form of a single string or of a string followed by a value.
%
%   'csinv_refl_coeff' Uses the FFT of the reflection coefficient as input
%                   to fast inverse scattering stage when inverting the
%                   continuous spectrum (default).
%   'csinv_a_from_b_iter' Use A(z) and B(z) as inputs to the fast inverse
%                   scattering stage, where A(z) is build from B(z) in an
%                   iterative manner. Defocusing case (kappa=-1) only
%   'csinv_b_from_a' Use A(z) and B(z) as inputs to the fast inverse
%                   scattering stage, where A(z) is generated first.
%   'csinv_b_from_a_wo_specfact' Same as 'csinv_b_from_a', except that the
%                   spectral factorization is skipped.
%   'quiet'         Turns off messages generated by then FNFT C library.
%                   (To turn off the messages generated by the mex
%                   interface functions, use Matlab's warning and error
%                   commands instead.)
%
% OUTPUTS
%   q               Complex row vector of length D

% This file is part of FNFT.  
%                                                                  
% FNFT is free software; you can redistribute it and/or
% modify it under the terms of the version 2 of the GNU General
% Public License as published by the Free Software Foundation.
%
% FNFT is distributed in the hope that it will be useful,
% but WITHOUT ANY WARRANTY; without even the implied warranty of
% MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
% GNU General Public License for more details.
%                                                                      
% You should have received a copy of the GNU General Public License
% along with this program. If not, see <http://www.gnu.org/licenses/>.
%
% Contributors:
% Sander Wahls (TU Delft) 2017-2018.
