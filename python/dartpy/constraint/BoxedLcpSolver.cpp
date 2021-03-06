/*
 * Copyright (c) 2011-2019, The DART development contributors
 * All rights reserved.
 *
 * The list of contributors can be found at:
 *   https://github.com/dartsim/dart/blob/master/LICENSE
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

#include <dart/dart.hpp>
#include <pybind11/pybind11.h>

namespace dart {
namespace python {

void BoxedLcpSolver(pybind11::module& m)
{
  ::pybind11::class_<
      dart::constraint::BoxedLcpSolver,
      std::shared_ptr<dart::constraint::BoxedLcpSolver>>(m, "BoxedLcpSolver")
      .def(
          "getType",
          +[](const dart::constraint::BoxedLcpSolver* self)
              -> const std::string& { return self->getType(); },
          ::pybind11::return_value_policy::reference_internal)
      .def(
          "solve",
          +[](dart::constraint::BoxedLcpSolver* self,
              int n,
              double* A,
              double* x,
              double* b,
              int nub,
              double* lo,
              double* hi,
              int* findex) { self->solve(n, A, x, b, nub, lo, hi, findex); },
          ::pybind11::arg("n"),
          ::pybind11::arg("A"),
          ::pybind11::arg("x"),
          ::pybind11::arg("b"),
          ::pybind11::arg("nub"),
          ::pybind11::arg("lo"),
          ::pybind11::arg("hi"),
          ::pybind11::arg("findex"));
}

} // namespace python
} // namespace dart
