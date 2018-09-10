clc
clear
p=[];
l=1;
tic
for N=1:20:2000
    A=rand(N);
    B=rand(N);
    C=zeros(N);
    N
    for index=1:10
        t1=clock;
        for i=1:N
            for j=1:N
                for k=1:N
                    C(i,j)=C(i,j)+A(i,k)*B(k,j);
                end
            end
        end
        t2=clock;
        p(l,index)=2*N^3./etime(t2,t1);
    end
    l=l+1;
end
toc

