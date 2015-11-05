/*
 *    This file is part of CasADi.
 *
 *    CasADi -- A symbolic framework for dynamic optimization.
 *    Copyright (C) 2010-2014 Joel Andersson, Joris Gillis, Moritz Diehl,
 *                            K.U. Leuven. All rights reserved.
 *    Copyright (C) 2011-2014 Greg Horn
 *
 *    CasADi is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License as published by the Free Software Foundation; either
 *    version 3 of the License, or (at your option) any later version.
 *
 *    CasADi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with CasADi; if not, write to the Free Software
 *    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */


#ifndef CASADI_QP_SOLVER_HPP
#define CASADI_QP_SOLVER_HPP

#include "function_internal.hpp"
#include "plugin_interface.hpp"

/// \cond INTERNAL
namespace casadi {
  /// Structure specification of a QP
  enum QPStruct {
    /// The square matrix H: sparse, (n x n). Only the lower triangular part is actually used.
    /// The matrix is assumed to be symmetrical.
    QP_STRUCT_H,
    /// The matrix A: sparse, (nc x n) - product with x must be dense.
    QP_STRUCT_A,
    QP_STRUCT_NUM};

  /// Internal class
  class CASADI_EXPORT
  QpSolver : public FunctionInternal,
                     public PluginInterface<QpSolver> {
  public:

    // Constructor
    QpSolver(const std::string& name, const std::map<std::string, Sparsity> &st);

    // Destructor
    virtual ~QpSolver() = 0;

    ///@{
    /** \brief Number of function inputs and outputs */
    virtual size_t get_n_in() const { return QP_SOLVER_NUM_IN;}
    virtual size_t get_n_out() const { return QP_SOLVER_NUM_OUT;}
    ///@}

    /// @{
    /** \brief Sparsities of function inputs and outputs */
    virtual Sparsity get_sparsity_in(int ind) const;
    virtual Sparsity get_sparsity_out(int ind) const;
    /// @}

    // Initialize
    virtual void init();

    // Solve the system of equations
    virtual void evaluate();

    // Solve the system of equations
    virtual void solve();

    /// \brief Check if the numerical values of the supplied bounds make sense
    virtual void checkInputs() const;

    /** Generate native code in the interfaced language for debugging */
    virtual void generateNativeCode(std::ostream& file) const;

    // Creator function for internal class
    typedef QpSolver* (*Creator)(const std::string& name,
                                         const std::map<std::string, Sparsity>& st);

    // No static functions exposed
    struct Exposed{ };

    /// Collection of solvers
    static std::map<std::string, Plugin> solvers_;

    /// Infix
    static const std::string infix_;

    /// Short name
    static std::string shortname() { return "qpsol";}

    /** \brief Get default input value */
    virtual const double& default_in(int ind) const;

  protected:

    /// Problem structure
    std::vector<Sparsity> st_;

    /// Number of decision variables
    int n_;

    /// The number of constraints (counting both equality and inequality) == A.size1()
    int nc_;
  };


} // namespace casadi
/// \endcond
#endif // CASADI_QP_SOLVER_HPP

