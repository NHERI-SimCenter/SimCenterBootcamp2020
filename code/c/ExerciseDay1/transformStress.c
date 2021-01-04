// program to transform stress:
//
// sigmaX' = sigmaX * cos^2(theta) + sigmaY * sin^2(theta) + 2 * tauXY Sin(theta)Cos(theta)
// sigmaY' = sigmaX * sin^2(theta) + sigmaY * cos^2(theta) - 2 * tauXY Sin(theta)Cos(theta)
// tauXY' = (sigmaX-sigmaY) * sin(theta)cos(theta) + tauXY(cos^2(theta) - sin^2(theta))
//
// write a program to take 4 inputs: sigmaX, sigmaY, tauXY, theta
// output transformed stresses: sigmaX', sigmaY', tauXY'
//
// NOTE: perform the transformation inside a function that cannot be named main

