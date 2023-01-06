# `libpascalreal` - C APIs for using Turbo Pascal 48-bit floating-point numbers

This is a (very) small library meant to provide interfaces for converting Turbo
Pascal `real` into C `double` and back.

Information about this format is scarce, and it appears to never have been
officially documented, so this implementation (like any other) cannot be
reliably treated as a reference one.

# Compilation

You're encouraged to integrate this library directly into your project. The only
thing that's needed is a C99 compiler with a math library.

# Known issues / caveats

* The library was not tested with a compiler or platform that doesn't use the
  double-precision IEEE 754 floating-point format for representing the `double`
  type.
* Denormals, NaNs and infinities are converted to negative zero.
* Numbers too large to be expressed as a `real` are converted to the maximum
  legal value.
* Similarly, numbers too small are converted to zero.

# The format

8-bit exponent with an exponent offset of 129, 39-bit mantissa and a sign bit.

According to _Delphi in a Nutshell_ by Ray Lischner released in March 2000, this
type is (was?) supported by Delphi as well under the name `Real48`.

Additionally, it straight out states that

> It cannot store denormalized values, infinity, or not-a-number. If the
> exponent is zero, the number is zero.

[(source)](https://www.oreilly.com/library/view/delphi-in-a/1565926595/re260.html)

## Memory layout

```
 0        1        2        3        4        5        
 76543210 76543210 76543210 76543210 76543210 76543210 
+--------+--------+--------+--------+--------+--------+
|EEEEEEEE|MMMMMMMM|MMMMMMMM|MMMMMMMM|MMMMMMMM|SMMMMMMM|
+--------+--------+--------+--------+--------+--------+
```

## Real-world usage

According to [Modding Wiki](https://moddingwiki.shikadi.net/wiki/Turbo_Pascal_Real),
this binary format is used by save game files by some games written in Turbo
Pascal.

It is also used in a Polish industrial automation protocol called GAZ-MODEM
(later renamed GAZ-MODEM 1), standardised by PGNiG in ZN-G-4007:1995 Appendix A.

# Legal

The licence of the library itself is available in `LICENCE.BSD`.
