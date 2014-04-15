/*
 * Copyright (c) 2014, Georgia Tech Research Corporation
 * All rights reserved.
 *
 * Author(s): Jeongseok Lee <jslee02@gmail.com>
 *
 * Geoorgia Tech Graphics Lab and Humanoid Robotics Lab
 *
 * Directed by Prof. C. Karen Liu and Prof. Mike Stilman
 * <karenliu@cc.gatech.edu> <mstilman@cc.gatech.edu>
 *
 * This file is provided under the following "BSD-style" License:
 *   Redistribution and use in source and binary forms, with or
 *   without modification, are permitted provided that the following
 *   conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 *   CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 *   INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *   MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 *   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 *   USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 *   AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *   ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *   POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef DART_CONSTRAINT_CONTACTCONSTRAINT_H_
#define DART_CONSTRAINT_CONTACTCONSTRAINT_H_

#include "dart/constraint/Constraint.h"

#include "dart/math/MathTypes.h"
#include "dart/collision/CollisionDetector.h"

// Note: ODE's dSolve uses fixed number of friction cone bases as 4
//#define DART_MIN_NUM_FRICTION_CONE_BASES 4
//#define DART_MAX_NUM_FRICTION_CONE_BASES 16
//#define DART_DEFAULT_NUM_FRICTION_CONE_BASES 2

// TODO: Max contact number

namespace dart {

namespace dynamics {
class BodyNode;
class Skeleton;
}  // namespace dynamics

namespace constraint {

/// ContactConstraint represents a contact constraint between two bodies
class ContactConstraint : public Constraint
{
public:
  /// Constructor
  ContactConstraint(const collision::Contact& _contact);

  /// Default destructor
  virtual ~ContactConstraint();

  //----------------------------------------------------------------------------
  // Settings
  //----------------------------------------------------------------------------
  /// Set first frictional direction
  void setFirstFrictionDir(const Eigen::Vector3d& _dir);

  /// Get first frictional direction
  const Eigen::Vector3d& getFirstFrictionlDir() const;

  //----------------------------------------------------------------------------
  // Constraint virtual function
  //----------------------------------------------------------------------------
  // Documentaion inherited
  virtual void update();

  // Documentaion inherited
  virtual void fillLcpOde(ODELcp* _lcp, int _idx);

  // Documentaion inherited
  virtual void applyUnitImpulse(int _idx);

  // Documentaion inherited
  virtual void getVelocityChange(double* _delVel, int _idx, bool _withCfm);

  // Documentaion inherited
  virtual void excite();

  // Documentaion inherited
  virtual void unexcite();

  // Documentaion inherited
  virtual void applyConstraintImpulse(double* _lambda, int _idx);

  //----------------------------------------------------------------------------
  // Solving
  //----------------------------------------------------------------------------
  ///
  bool isActive();

  // Documentation inherited
  virtual dynamics::Skeleton* getRootSkeleton() const;

  // Documentation inherited
  virtual void uniteSkeletons();

protected:
  /// Fircst body node
  dynamics::BodyNode* mBodyNode1;

  /// Second body node
  dynamics::BodyNode* mBodyNode2;

  /// Contacts between mBodyNode1 and mBodyNode2
  std::vector<collision::Contact> mContacts;

  /// First frictional direction
  Eigen::Vector3d mFirstFrictionalDirection;

  /// Constraint error redection parameter in range of [0, 1]
  double mErrorReductionParameter;

  /// Coefficient of Friction
  double mFrictionCoeff;

  /// Coefficient of restitution
  double mRestitutionCoeff;

private:
  /// Get change in relative velocity at contact point due to external impulse
  /// \param[out] _relVel Change in relative velocity at contact point of the
  ///                     two colliding bodies
  /// \param[in] _idx Index the relative velocity change will be stored
  void getRelVelocity(double* _relVel, int _idx);

  /// Compute change in velocity due to _idx-th impulse.
  void updateVelocityChange(int _idx);

  ///
  void updateFirstFrictionalDirection();

  ///
  Eigen::MatrixXd getTangentBasisMatrixODE(const Eigen::Vector3d& _n);

  /// Local body jacobians for mBodyNode1
  std::vector<Eigen::Vector6d> mJacobians1;

  /// Local body jacobians for mBodyNode2
  std::vector<Eigen::Vector6d> mJacobians2;

  ///
  bool mIsFrictionOn;

  /// Small value to add to diagnal of A matrix of LCP to keep it away
  /// from singular, similar to cfm varaible in ODE. Default is 0.001.
  double mCfm;

  /// Index of applied impulse
  size_t mAppliedImpulseIndex;

  ///
  bool mIsBounceOn;

  ///
  bool mActive;
};

} // namespace constraint
} // namespace dart

#endif  // DART_CONSTRAINT_IBCONTACTCONSTRAINT_H_

