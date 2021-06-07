// To solve this problem, we need to sample points within the fixed cicle such that the angle of the point wrt the x-axis is chosen uniformly at random. That's the easy part. The harder part is to figure out how to randomly choose the distance of the point from the center of the circle.

// For this, we need to compute the probability of the point falling between radii r and r+del_r. This is simply the ratio of the area of the circular strip confined between radii r and r+del_r as the numerator and the area of the whole circle as the denominator. This is equal to (PI*(r+del_r)^2 - PI*r^2) / (PI*R^2), or simply 2*r*del_r / R^2. Clearly, this is not a uniform distribution, so using a library function such as rand.Float64 to sample r will not give us the right results since these functions sample from a uniform distribution.

// We now seek another uniformly distributed random variable which happens to be a mathematical function of the random variable r. If we can find such a variable, then we can use facilities such as rand.Float64 to generate a value for that random variable and reverse engineer a value for r from that.

// Our first guess ought to be the variable r^2. And as we shall see soon, this does the job as expected. The probability that r^2 has a value less than say H is same as the probability that r has a value less than sqrt(H). We can get the latter probabillity using simple integral calculus by integrating the function 2*r*del_r / R^2 across the range [0, sqrt(H)]. This yields the value H / R^2. So, the probability that r^2 takes on a value between H and H+del_H is del_H / R^2, which is the same no matter the value of r^2, so it is a uniform distribution. 

import (
    "math"
    "math/rand"
    "time"
)

type Solution struct {
   Radius float64
   X_center float64
   Y_center float64
}


func Constructor(radius float64, x_center float64, y_center float64) Solution {
    rand.Seed(time.Now().UnixNano())
    return Solution{Radius: radius, X_center: x_center, Y_center: y_center}
}


func (this *Solution) RandPoint() []float64 {
    rand_r_square := rand.Float64() * math.Pow(this.Radius, 2.0)
    rand_r := math.Sqrt(rand_r_square)

    rand_angle := rand.Float64() * 2.0 * math.Pi

    return []float64{ this.X_center + rand_r * math.Cos(rand_angle), this.Y_center + rand_r * math.Sin(rand_angle) }
}


/**
 * Your Solution object will be instantiated and called as such:
 * obj := Constructor(radius, x_center, y_center);
 * param_1 := obj.RandPoint();
 */
