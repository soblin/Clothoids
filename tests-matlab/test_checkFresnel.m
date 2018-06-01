addpath('../matlab');

%=============================================================================%
%                                                                             %
%  Autors: Enrico Bertolazzi                                                  %
%          Department of Industrial Engineering                               %
%          University of Trento                                               %
%          enrico.bertolazzi@unitn.it                                         %
%          m.fregox@gmail.com                                                 %
%                                                                             %
%=============================================================================%
% Driver test program to check bounding box on clothoid                       %
%=============================================================================%

% Values computed with MAPLE for comparison
points = {...
[0.98,.779269472398985793616327384272, .418272107748504825551976929861],...
[0.99,.779736857107398554436539155996, .428260779932261971530215184381],...
[1,.779893400376822829474206413653, .438259147390354766076756696625],...
[1.001,.779891829058190737708252359854, .439259145744187565034292113231],...
[1.01,.779735810219893754553825900991, .448257490177142316568579965897],...
[1.1,.763806666062011990726130009285, .536497911096820434834597659214],...
[5,.563631188704012231102107404413,.499191381917116886751928380466],...
[3,.605720789297685629556161074287, .496312998967375036097612265299],...
[5.9,.448591953169830103017721555043, .516330691504153765822181121410],...
[5.99,.489590506663209554379464570908, .447899933737726235290994948996],...
[6.001,.500531408631524565149385550388, .446970186259380823477483976076],...
[6.01,.509472281587403320380847768367, .447900969796601504809051331172],...
[6.1,.549502201263965312163051641321, .516477082795104011077749562072],...
[10,.499898694205515723614151847736, .468169978584882240403351110810],...
[100,.499999898678817897559468463526, .496816901147837553271467023384],...
[1000,.499999999898678816357816218290, .499681690113816306083065531729],...
[10000,.499999999999898678816357662244, .499968169011381620933813769280]};

for k=1:length(points)
  pt = points{k} ;
  [C,S] = FresnelCS(pt(1)) ;
  fprintf(1,'x=%5g err = [%10g,%10g] [C,S] = [%14g,%14g]\n',pt(1),C,S,C-pt(2),S-pt(3)) ;	
end
