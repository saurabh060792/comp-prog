v = map(int,raw_input().split())
s = sum(v)
print min(s/3,s-max(v))

#Let t1, t2 and t3 (t1<t2<t3) be the number of balloons of red, green and
#blue color, s be the sum that is t1 + t2 + t3 and t is the maximum
#balloons used. 

#Claim 1: t <= floor(s/3)
#Proof: Trivial. Assume that t>floor(s/3). Let r,b and g are balloons used
#in arrangement corresponding to maximum. So, r+g+b>s but r<=t1, g<=t2
#b<=t3 and t1+t2+t3 = s. A contradiction.

#Claim 2: When 2(t1+t2) >= t3 then t = s/3 else t = t1 + t2
#Proof : When 2(t1+t2)<t3, the arrangement which attains the maximum
#table will have 2 blue(t3) balloons in all the table. We can show 
#this by assuming that the max t arrangement has one or more table
#which has all the three different colors of balloons. Then we can
#always set one more table by replacing one color(not blue) from that
#table by blue and then use 2 more blue balloons from remaining blue
#balloon and the balloon which we just remove. We can always find
#2 blue balloons for the balloon which was replaced because
#we have 2 blue balloons for every red and green balloons
#as 2(t1+t2)<t3. Hence maximum will achieve when all the tables
#have 2 blue balloons.So t = t1+t2.
#when 2(t1+t2)>=t3, we use the tactics of taking two balloons
#from max and one from second max.

