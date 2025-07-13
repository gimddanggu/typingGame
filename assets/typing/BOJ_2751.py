# 수 정렬하기
import sys
input = sys.stdin.readline
n = int(input())
lis = [int(input()) for i in range(n)]
lis.sort()
print(*lis, sep='\n')