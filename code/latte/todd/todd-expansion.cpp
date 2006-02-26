#include "todd-expansion.h"

mpq_vector
taylor_exponential(int order)
{
  mpq_vector result(order + 1);
  mpq_class coeff(1);
  int i;
  for (i = 0; i<=order; i++, coeff /= i) 
    result[i] = coeff;
  return result;
}

mpq_vector
taylor_reciprocal(const mpq_vector &a)
{
  // Make the ansatz 1 / (a_0 t^0 + a_1 t^1 + a_2 t^2 + ...)
  //                   = (b_0 t^0 + b_1 t^1 + b_2 t^2 + ...)
  // and solve for the b_i.
  mpq_vector b(a.size());
  // Compute the first coefficient.
  b[0] = 1 / a[0];
  int i;
  for (i = 1; i<a.size(); i++) {
    // We have 0 = a_0 b_i + a_1 b_{i-1} + ... + a_i b_0.
    // Compute b_i from that.
    int j;
    mpq_class sum = 0;
    for (j = 1; j<=i; j++)
      sum += a[j] * b[i-j];
    b[i] = -sum / a[0];
  }
  return b;
}

mpq_vector
taylor_for_todd(int order)
{
  // Prepare exp(t).
  mpq_vector exp = taylor_exponential(order + 2);
  // We want t/(1-exp(t)); we can cancel one t here.
  mpq_vector todd_denom(order + 1);
  int i;
  for (i = 0; i<=order; i ++)
    todd_denom[i] = -exp[i+1];
  return taylor_reciprocal(todd_denom);
}

static mpq_vector
taylor_product_aux(const mpq_vector &a, const mpq_vector &b)
{
  int size = min(a.size(), b.size());
  mpq_vector result(size);
  int i;
  for (i = 0; i<size; i++) {
    mpq_class sum = 0;
    int j;
    for (j = 0; j<=i; j++)
      sum += a[j] * b[i-j];
    result[i] = sum;
  }
  return result;
}

mpq_vector
taylor_product(const vector<mpq_vector> &taylors)
{
  vector<mpq_vector>::const_iterator p = taylors.begin();
  if (p == taylors.end()) {
    // Return 1.
    mpq_vector result(1);
    result[0] = 1;
    return result;
  }
  mpq_vector result(*p);
  for (++p; p != taylors.end(); ++p)
    result = taylor_product_aux(result, *p);
  return result;
}

mpq_vector
evaluate_todd(const mpz_vector &x)
{
  int dimension = x.size();
  // Compute Taylor series for t/(1-exp(t))
  mpq_vector factor = taylor_for_todd(dimension);
  // Substitute t -> x_i * t
  vector<mpq_vector> factors(dimension);
  int i;
  for (i = 0; i<dimension; i++) {
    factors[i] = mpq_vector(factor.size());
    mpq_vector::const_iterator source;
    mpq_vector::iterator dest;
    mpz_class coefficient = 1;
    for (source = factor.begin(), 
	   dest = factors[i].begin(),
	   coefficient = 1;
	 source != factor.end();
	 ++source, ++dest, coefficient *= x[i])
      (*dest) = coefficient * (*source);
  }
  // Compute their product
  return taylor_product(factors);
}
