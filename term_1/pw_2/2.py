from math import cos, exp, log, sin, tan


def G(m, n):
    return (abs( m - n ) ** 0.5 - sin( m ) * cos( n )) / (log( tan( m / n ) ) + exp( m ** 2 ))

print(G(10, 0))