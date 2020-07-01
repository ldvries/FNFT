/*
 * This file is part of FNFT.
 *
 * FNFT is free software; you can redistribute it and/or
 * modify it under the terms of the version 2 of the GNU General
 * Public License as published by the Free Software Foundation.
 *
 * FNFT is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * Contributors:
 * Sander Wahls (TU Delft) 2017.
 * Shrinivas Chimmalgi (TU Delft) 2017-2020.
 */

/**
 * @brief Properties of the discretizations for the nonlinear Schroedinger
 * equation.
 *
 * @file fnft__nse_discretization.h
 * @ingroup nse
 */

#ifndef FNFT__NSE_DISCRETIZATION_H
#define FNFT__NSE_DISCRETIZATION_H

#include "fnft_nse_discretization_t.h"
#include "fnft__akns_discretization.h"
#include "fnft__misc.h"




/**
 * @brief This routine returns the max degree \f$d\f$ of the polynomials in a single
 * scattering matrix or zero if the discretization is unknown.
 *
 * @param[in] nse_discretization The type of discretization to be used. Should be
 * of type \link fnft_nse_discretization_t \endlink.
 * @returns polynomial degree, or 0 for discretizations not supported by \link fnft__nse_fscatter \endlink.
 *
 * @ingroup nse
 */
FNFT_UINT fnft__nse_discretization_degree(fnft_nse_discretization_t
        nse_discretization);

/**
 * @brief This routine returns the boundary coefficient based on the
 * discretization.
 *
 * The boundary coefficient is the fraction of the step size that a discretized
 * potential extends beyond the last sample. This routine returns this value
 * based on the discretization of type \link fnft_nse_discretization_t \endlink.
 * @param[in] nse_discretization The type of discretization to be used. Should be
 * of type \link fnft_nse_discretization_t \endlink.
 * @returns the boundary coefficient, or NAN for discretizations not supported
 * by \link fnft__nse_fscatter \endlink.
 *
 * @ingroup nse
 */
FNFT_REAL fnft__nse_discretization_boundary_coeff(fnft_nse_discretization_t nse_discretization);

/**
 * @brief This routine returns the scaling for effective number of samples based on the
 * discretization.
 *
 * Higher order methods use more than one sample per integration step. This routine returns
 * the value upsampling_factor based on the discretization of type \link fnft_nse_discretization_t \endlink.
 * D_effective = upsampling_factor * D.
 * @param[in] discretization The type of discretization to be used. Should be
 * of type \link fnft_nse_discretization_t \endlink.
 * @returns the upsampling_factor value, or 0 for discretizations not supported
 * by \link fnft__nse_fscatter \endlink.
 *
 * @ingroup nse
 */
FNFT_UINT fnft__nse_discretization_upsampling_factor(fnft_nse_discretization_t discretization);

/**
 * @brief This routine returns the order of the method based on the
 * discretization.
 *
 * Different numerical methods have different orders of accuray. This routine returns
 * the order of the order based on the discretization of type \link fnft_nse_discretization_t \endlink.
 * When the step-size of the signal samples is reduced by a factor \f$s\f$, the error in the
 * computed values is expected to decrease by a factor \f$s^{order}\f$.
 * @param[in] discretization The type of discretization to be used. Should be
 * of type \link fnft_nse_discretization_t \endlink.
 * @returns the method_order value, or 0.
 *
 * @ingroup nse
 */
FNFT_UINT fnft__nse_discretization_method_order(fnft_nse_discretization_t discretization);


/**
 * @brief This routine returns akns discretization related to the given
 * nse discretization.
 *
 * The function is used by nse specific functions to convert discretization type from 
 * \link fnft_nse_discretization_t \endlink to \link fnft__akns_discretization_t \endlink.
 * @param[in] nse_discretization The type of nse discretization. Should be
 * of type \link fnft_nse_discretization_t \endlink.
 * @param[out] akns_discretization The pointer to the converted discretization
 * of type \link fnft__akns_discretization_t \endlink.
 * @return \link FNFT_SUCCESS \endlink or one of the FNFT_EC_... error codes
 *  defined in \link fnft_errwarn.h \endlink.
 *
 * @ingroup nse
 */
FNFT_INT fnft__nse_discretization_to_akns_discretization(fnft_nse_discretization_t nse_discretization, 
        fnft__akns_discretization_t * const akns_discretization);
        
        
/**
 * @brief This routine maps \f$\lambda\f$ from continuous-time domain to
 * \f$z\f$ in the discrete-time domain based on the discretization. 
 * 
 * This routine maps continuous-time domain value lambda to discrete-time domain value
 * \f$z = e^{2j\lambda\epsilon_t degree1step)\f$, where degree1step is based on the discretization 
 * of type \link fnft_nse_discretization_t \endlink. Changes discretization to 
 * \link fnft__akns_discretization_t \endlink type and calls \link fnft__akns_lambda_to_z \endlink.
 * @param[in] n Number of values to be mapped.
 * @param[in] eps_t Real-valued discretization step-size.
 * @param[in,out] vals Pointer to location of first element of array containing
 * complex-valued continuous-time domain spectral parameter \f$\lambda\f$. The values are replaced with
 * discrete-time domain values \f$z\f$.
 * @param[in] discretization Discretization of type \link fnft_nse_discretization_t \endlink.
 * @return \link FNFT_SUCCESS \endlink or one of the FNFT_EC_... error codes
 *  defined in \link fnft_errwarn.h \endlink.
 *
 * @ingroup nse
 */
FNFT_INT fnft__nse_lambda_to_z(const FNFT_UINT n, const FNFT_REAL eps_t, 
        FNFT_COMPLEX * const vals, fnft_nse_discretization_t discretization);

/**
 * @brief This routine maps \f$z\f$ from the discrete-time domain to
 * \f$\lambda\f$ in the continuous-time domain based on the discretization. 
 * 
 * This routine maps discrete-time domain value \f$z\f$ to continuous-time domain value
 * \f$\lambda = degree1step\log(z)/(2j\epsilon_t)\f$, where degree1step is based on the discretization 
 * of type \link fnft_nse_discretization_t \endlink. Changes discretization to 
 * \link fnft__akns_discretization_t \endlink type and calls \link fnft__akns_z_to_lambda \endlink.
 * @param[in] n Number of values to be mapped.
 * @param[in] eps_t Real-valued discretization step-size.
 * @param[in,out] vals Pointer to location of first element of array containing
 * complex-valued discrete-time domain spectral parameter \f$z\f$. The values are replaced with
 * continuous-time domain values \f$\lambda\f$.
 * @param[in] discretization Discretization of type \link fnft_nse_discretization_t \endlink.
 * @return \link FNFT_SUCCESS \endlink or one of the FNFT_EC_... error codes
 *  defined in \link fnft_errwarn.h \endlink.
 *
 * @ingroup nse
 */
FNFT_INT fnft__nse_z_to_lambda(const FNFT_UINT n, const FNFT_REAL eps_t, 
        FNFT_COMPLEX * const vals, fnft_nse_discretization_t discretization);

/**
 * @brief  This routine returns the phase factor for reflection coefficient (\f$\rho\f$).
 * It is required for applying boundary conditions to the transfer_matrix based on the discretization. 
 * 
 * This routine computes the phase correction factor for the computation of the 
 * reflection coefficient from the transfer_matrix. phase_factor_rho = -2.0*(T1 + eps_t*boundary_coeff),
 * where eps_t is the step-size, T1 is the time at the right-boundary and boundary_coeff is based on the
 * discretization of type \link fnft_nse_discretization_t \endlink.  Only for fnft_nse_discretization_2SPLIT2A
 * and fnft_nse_discretization_2SPLIT2_MODAL, phase_factor_rho = -2.0*(T1 + eps_t*boundary_coeff)+eps_t/degree1step
 * where degree1step is based on the discretization of type \link fnft_nse_discretization_t \endlink. 
 * @param[in] eps_t Real-valued discretization step-size.
 * @param[in] T1 Real-valued time at the right-boundary.
 * @param[in,out] phase_factor_rho Pointer to real-valued variable where the computed phase factor will be stored.
 * @param[in] nse_discretization Discretization of type \link fnft_nse_discretization_t \endlink.
 * @return \link FNFT_SUCCESS \endlink or one of the FNFT_EC_... error codes
 *  defined in \link fnft_errwarn.h \endlink.
 *
 * @ingroup nse
 */
FNFT_INT fnft__nse_phase_factor_rho(const FNFT_REAL eps_t, const FNFT_REAL T1,
        FNFT_REAL * const phase_factor_rho, fnft_nse_discretization_t nse_discretization);

/**
 * @brief  This routine returns the phase factor for a coefficient.
 * It is required for applying boundary conditions to the transfer_matrix based on the discretization. 
 * 
 * This routine computes the phase correction factor for the computation of the 
 * a coefficient from the transfer_matrix. phase_factor_a = -eps_t*D + (T[1]+eps_t*boundary_coeff) - (T[0]-eps_t*boundary_coeff),
 * where eps_t is the step-size, D is the number of samples used to build the transfer_matrix, 
 * T is the 2-element time vector defining the signal support and boundary_coeff is based on the
 * discretization of type \link fnft_nse_discretization_t \endlink.
 * @param[in] eps_t Real-valued discretization step-size.
 * @param[in] D Positive interger number of samples used to build transfer_matrix.
 * @param[in] T Real-valued 2-element time vector defining the signal support.
 * @param[in,out] phase_factor_a Pointer to real-valued variable where the computed phase factor will be stored.
 * @param[in] nse_discretization Discretization of type \link fnft_nse_discretization_t \endlink.
 * @return \link FNFT_SUCCESS \endlink or one of the FNFT_EC_... error codes
 *  defined in \link fnft_errwarn.h \endlink.
 *
 * @ingroup nse
 */
FNFT_INT fnft__nse_phase_factor_a(const FNFT_REAL eps_t, const FNFT_UINT D, FNFT_REAL const * const T,
        FNFT_REAL * const phase_factor_a, fnft_nse_discretization_t nse_discretization);

/**
 * @brief  This routine returns the phase factor for b coefficient.
 * It is required for applying boundary conditions to the transfer_matrix based on the discretization. 
 * 
 * This routine computes the phase correction factor for the computation of the 
 * a coefficient from the transfer_matrix. phase_factor_b = -eps_t*D - (T[1]+eps_t*boundary_coeff) - (T[0]-eps_t*boundary_coeff),
 * where eps_t is the step-size, D is the number of samples used to build the transfer_matrix, 
 * T is the 2-element time vector defining the signal support and boundary_coeff is based on the
 * discretization of type \link fnft_nse_discretization_t \endlink.  Only for fnft_nse_discretization_2SPLIT2A
 * and fnft_nse_discretization_2SPLIT2_MODAL, phase_factor_b = -eps_t*D - (T[1]+eps_t*boundary_coeff) - (T[0]-eps_t*boundary_coeff)+ eps_t/degree1step
 * where degree1step is based on the discretization of type \link fnft_nse_discretization_t \endlink. 
 * @param[in] eps_t Real-valued discretization step-size.
 * @param[in] D Positive interger number of samples used to build transfer_matrix.
 * @param[in] T Real-valued 2-element time vector defining the signal support.
 * @param[in,out] phase_factor_b Pointer to real-valued variable where the computed phase factor will be stored.
 * @param[in] nse_discretization Discretization of type \link fnft_nse_discretization_t \endlink.
 * @return \link FNFT_SUCCESS \endlink or one of the FNFT_EC_... error codes
 *  defined in \link fnft_errwarn.h \endlink.
 *
 * @ingroup nse
 */
FNFT_INT fnft__nse_phase_factor_b(const FNFT_REAL eps_t, const FNFT_UINT D, FNFT_REAL const * const T,
        FNFT_REAL * const phase_factor_b, fnft_nse_discretization_t nse_discretization);
        

/**
 * @brief  This routine preprocesses the signal by resampling and subsampling based on the discretization.
 * The preprocessing is necessary for higher-order methods.
 * 
 * This routine preprocess q to generate q_preprocessed and r_preprocessed
 * based on the discretization. The preprocessing may involve resampling 
 * and sub-sampling. 
 * The routine is based on the following papers:
 *      - Chimmalgi, Prins and Wahls, <a href="https://doi.org/10.1109/ACCESS.2019.2945480">&quot; Fast Nonlinear Fourier Transform Algorithms Using Higher Order Exponential Integrators,&quot;</a> IEEE Access 7, 2019.
 *      - Medvedev, Vaseva, Chekhovskoy and  Fedoruk, <a href="https://doi.org/10.1364/OE.377140">&quot; Exponential fourth order schemes for direct Zakharov-Shabat problem,&quot;</a> Optics Express, vol. 28, pp. 20--39, 2020.
 *
 * @param[in] D Number of samples
 * @param[in] q Array of length D, contains samples \f$ q(t_n)=q(x_0, t_n) \f$,
 *  where \f$ t_n = T[0] + n(T[1]-T[0])/(D-1) \f$ and \f$n=0,1,\dots,D-1\f$, of
 *  the to-be-transformed signal in ascending order
 *  (i.e., \f$ q(t_0), q(t_1), \dots, q(t_{D-1}) \f$)
 * @param[in] eps_t Real-valued discretization step-size.
 * @param[in] kappa =+1 for the focusing nonlinear Schroedinger equation,
 *  =-1 for the defocusing one 
 * @param[out] q_preprocessed_ptr Pointer to the starting location of preprocessed signal q_preprocessed.
 * @param[out] r_preprocessed_ptr Pointer to the starting location of preprocessed signal r_preprocessed.
 * @param[in,out] Dsub_ptr Pointer to number of processed samples. Upon entry, *Dsub_ptr
 *             should contain a desired number of samples. Upon exit, *Dsub_ptr
 *             has been overwritten with the actual number of samples that the
 *             routine has chosen. It is usually close to the desired one.
 * @param[out] first_last_index Vector of length two. Upon exit, it contains
 *             the original index of the first and the last sample used to build
 *             q_preprocessed.
 * @param[in] discretization Discretization of type \link fnft_nse_discretization_t \endlink.
 * @return \link FNFT_SUCCESS \endlink or one of the FNFT_EC_... error codes
 *  defined in \link fnft_errwarn.h \endlink.
 *
 * @ingroup nse
 */
FNFT_INT fnft__nse_preprocess_signal(const FNFT_UINT D, FNFT_COMPLEX const * const q,
        FNFT_REAL const eps_t, const FNFT_INT kappa,
        FNFT_UINT * const Dsub_ptr, FNFT_COMPLEX **q_preprocessed_ptr, FNFT_COMPLEX **r_preprocessed_ptr,
        FNFT_UINT * const first_last_index,  fnft_nse_discretization_t discretization);


/**
 * @brief This routine computes various weights required by some methods
 * based on the discretization. 
 * 
 * This routing computes the special weights required for the 
 * higher-order methods CF\f$^{[4]}_2\f$, CF\f$^{[4]}_3\f$, CF\f$^{[5]}_3\f$ 
 * and CF\f$^{[6]}_4\f$. The weights are used in \link fnft__nse_preprocess_signal \endlink,
 * \link fnft__akns_scatter_matrix \endlink and \link fnft__nse_scatter_bound_states\endlink.
 * The weights for CF\f$^{[4]}_3\f$ are taken from Alvermann and Fehske (<a href="https://doi.org/10.1016/j.jcp.2011.04.006">Journal of Computational Phys. 230, 2011</a>)
 * and the weights for the others are from Blanes, Casas and Thalhammer(<a href="https://doi.org/10.1016/j.cpc.2017.07.016">Computer Phys. Comm. 220, 2017</a>).
 * The weights are mentioned as matrices in the references. This routine returns 
 * them in row-major order.
 * @param[in,out] weights_ptr Pointer to the starting location of weights.
 * @param[in] nse_discretization Discretization of type \link fnft_nse_discretization_t \endlink.
 * @return \link FNFT_SUCCESS \endlink or one of the FNFT_EC_... error codes
 *  defined in \link fnft_errwarn.h \endlink.
 *
 * @ingroup nse
 */
FNFT_INT fnft__nse_discretization_method_weights(FNFT_COMPLEX **weights_ptr,
        fnft_nse_discretization_t nse_discretization);
        
        

#ifdef FNFT_ENABLE_SHORT_NAMES
#define nse_discretization_degree(...) fnft__nse_discretization_degree(__VA_ARGS__)
#define nse_discretization_boundary_coeff(...) fnft__nse_discretization_boundary_coeff(__VA_ARGS__)
#define nse_discretization_to_akns_discretization(...) fnft__nse_discretization_to_akns_discretization(__VA_ARGS__)
#define nse_discretization_upsampling_factor(...) fnft__nse_discretization_upsampling_factor(__VA_ARGS__)
#define nse_discretization_method_order(...) fnft__nse_discretization_method_order(__VA_ARGS__)
#define nse_lambda_to_z(...) fnft__nse_lambda_to_z(__VA_ARGS__)
#define nse_z_to_lambda(...) fnft__nse_z_to_lambda(__VA_ARGS__)
#define nse_phase_factor_rho(...) fnft__nse_phase_factor_rho(__VA_ARGS__)
#define nse_phase_factor_a(...) fnft__nse_phase_factor_a(__VA_ARGS__)
#define nse_phase_factor_b(...) fnft__nse_phase_factor_b(__VA_ARGS__)
#define nse_preprocess_signal(...) fnft__nse_preprocess_signal(__VA_ARGS__)
#define nse_discretization_method_weights(...) fnft__nse_discretization_method_weights(__VA_ARGS__)

#endif

#endif
