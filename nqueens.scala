#!/usr/bin/env scala

import Math._

case class Queen(x: Int, y: Int)

class Solution(queens: List[Queen]) {
    val n = queens.length
    override def toString: String = {
        (0 to n - 1).map { i =>
            ((0 to n - 1).map { j =>
                if (queens contains Queen(i, j)) {
                    "1 "
                } else {
                    "0 "
                }
            }).mkString("")
        }.mkString("\n")
    }
}

val testSolution = new Solution(List(Queen(1, 1), Queen(2, 2), Queen(3, 3), Queen(0, 1)))
println(testSolution);
