#!/usr/bin/env scala

import Math._

trait Piece {
    def nonattacking(other: Queen): Boolean
}

case class Queen(x: Int, y: Int) extends Piece {
    def nonattacking(other: Queen): Boolean = {
        x != other.x && y != other.y && abs( other.x - x ) != abs( other.y - y )
    }
}

// A chessboard with some number of Queens pieces placed
class Solution(_queens: List[Queen]) {
    val queens = _queens
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

object NQueens {
    // Chessboard's latest added Queen is not attacking any other Queens
    def promising(solution: Solution): Boolean = {
        solution.queens match {
            case head +: tail => tail.forall(_ nonattacking head)
        }
    }

    // Recursive backtracing to find a full Solution with n Queen pieces
    def backtracking(n: Int, solution: Solution): Solution = {
        val hd::tail = solution.queens
        if (hd.x == n)
            backtracking(n, new Solution(Queen(tail.head.x + 1, tail.head.y) +: tail.tail))
        else if (promising(solution)) {
            if (solution.queens.length == n)
                solution
            else
                backtracking(n, new Solution(Queen(0, hd.y + 1) +: solution.queens))
        }
        else
            backtracking(n, new Solution(Queen(hd.x + 1, hd.y) +: tail))
    }
}

// toString
val toStringSolution = new Solution(List(Queen(0, 0), Queen(1, 1)))
assert("1 0 \n0 1 " == toStringSolution.toString)

// nonattacking
assert(Queen(1, 0) nonattacking Queen(2, 3))
assert(!( Queen(1, 0) nonattacking Queen(0, 1) ))

// promising
val solutionThatIsPromising = new Solution(List(Queen(0, 0), Queen(2, 4)))
val solutionThatIsNotPromising = new Solution(List(Queen(5, 5), Queen(2, 2)))
assert(NQueens.promising(solutionThatIsPromising))
assert(!NQueens.promising(solutionThatIsNotPromising))

// finding a solution
println(NQueens.backtracking(args(0).toInt, new Solution(List(Queen(0, 0)))))


