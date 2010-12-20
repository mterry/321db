TABLE S (
  ATTR SNO, VARCHAR2(3), PRIMARY;
  ATTR SNAME, VARCHAR2(10);
  ATTR STATUS, NUMBER;
  ATTR CITY, VARCHAR2(10);
)
TABLE P (
  ATTR PNO, VARCHAR2(3), PRIMARY;
  ATTR PNAME, VARCHAR2(10);
  ATTR COLOR, VARCHAR2(5);
  ATTR WEIGHT, DECIMAL;
  ATTR CITY, VARCHAR2(10);
)
TABLE SP (
  ATTR SNO, VARCHAR2(3), PRIMARY, FOREIGN S(SNO); 
  ATTR PNO, VARCHAR2(3), PRIMARY, FOREIGN P(PNO);
  ATTR QTY, NUMBER;
)
