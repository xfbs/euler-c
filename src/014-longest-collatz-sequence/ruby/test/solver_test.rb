require 'minitest/autorun'
require_relative '../src/solver'

class SolverTest < MiniTest::Test
  def setup
  end

  def test_solve
    assert_equal Solver.solve(10), 9
  end
end
