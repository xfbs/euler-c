require "minitest/autorun"
require "../src/prime"

class PrimeTest < Minitest::Test
  def setup
  end

  def test_primes
    p = Prime.new

    assert_equal p.nth(0), 2
    assert_equal p.nth(1), 3
    assert_equal p.nth(2), 5
    assert_equal p.nth(3), 7
    assert_equal p.nth(4), 11
    assert_equal p.nth(5), 13
    assert_equal p.nth(6), 17
    assert_equal p.nth(7), 19
  end
end
