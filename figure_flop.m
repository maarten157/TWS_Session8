fid  = fopen( 'no_temp.txt', 'r') ; % tekstbestand met output
a = textscan(fid, '%f %f %f');
t_1=a{1,2};
n_1=a{1,1};
fid  = fopen( 'with_temp.txt', 'r') ; % tekstbestand met output
a = textscan(fid, '%f %f %f');
t_2=a{1,2};
n_2=a{1,1};

figure
%yyaxis left
loglog(n_1,t_1,'linewidth',1.5), hold on, loglog(n_1,n_1.^3.*10^-8.5,':','linewidth',1.5)
loglog(n_2,t_2,'linewidth',1.5), loglog(n_2,n_2.^2.*10^-8.5,':','linewidth',1.5)
%yyaxis right


xlabel('N')
ylabel('tijd [s]')
grid on, grid minor
set(gca,'fontsize',16)
title('Tijdsmeting expresie templates')
legend('zonder temp variabele','O(N^3)','met temp variabele','O(N^2)','location','northwest')

print('Figure','-dpng')
