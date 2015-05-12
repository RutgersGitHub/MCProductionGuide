C...A simple skeleton program, illustrating a typical Pythia run:
C...SemiLeptonicRPV production at CMS LHC.
C...Toy task: compare multiplicity distribution with matrix elements.
C...and with parton showers (using same fragmentation parameters).

C-----------------------------------------------------------------

C...Preamble: declarations.
 
C...All real arithmetic in double precision.
      IMPLICIT DOUBLE PRECISION(A-H, O-Z)
C...Three Pythia functions return integers, so need declaring.
      INTEGER PYK,PYCHGE,PYCOMP

C...EXTERNAL statement links PYDATA on most machines.
      EXTERNAL PYDATA

C...Commonblocks.
C...The event record.
      COMMON/PYJETS/N,NPAD,K(4000,5),P(4000,5),V(4000,5)
C...Parameters.
      COMMON/PYDAT1/MSTU(200),PARU(200),MSTJ(200),PARJ(200)
C...Particle properties + some flavour parameters.
      COMMON/PYDAT2/KCHG(500,4),PMAS(500,4),PARF(2000),VCKM(4,4)
C...Decay information.
      COMMON/PYDAT3/MDCY(500,3),MDME(8000,2),BRAT(8000),KFDP(8000,5)
C...Selection of hard scattering subprocesses.
      COMMON/PYSUBS/MSEL,MSELPD,MSUB(500),KFIN(2,-40:40),CKIN(200)
C...Parameters. 
      COMMON/PYPARS/MSTP(200),PARP(200),MSTI(200),PARI(200)
C...Supersymmetry parameters.
      COMMON/PYMSSM/IMSS(0:99),RMSS(0:99)
C...R-parity-violating couplings in supersymmetry.
      COMMON/PYMSRV/RVLAM(3,3,3), RVLAMP(3,3,3), RVLAMB(3,3,3)
C...Random Seed.
      COMMON/PYDATR/MRPY(6),RRPY(100)

C-----------------------------------------------------------------

C...First section: initialization.
      LOGICAL debug
      INTEGER randomseed, numevnt
      REAL sqrtSinGeV, gluinomass, squarkmass
      CHARACTER coupling*200, slhaoutput*200, txtoutput*200, lheoutput*200

      debug = .TRUE.

C...Reading in the names for all output files.
      READ(*,*) randomseed, numevnt, sqrtSinGeV, gluinomass, squarkmass, coupling, slhaoutput, txtoutput, lheoutput

      MRPY(1) = randomseed   ! sets the random seed pythia will use

      IF (debug .EQV. .TRUE.) THEN
        WRITE(*,*) randomseed, numevnt, sqrtSinGeV, gluinomass, squarkmass
        WRITE(*,*) trim(coupling)
        WRITE(*,*) trim(slhaoutput)
        WRITE(*,*) trim(txtoutput)
        WRITE(*,*) trim(lheoutput)
        WRITE(*,*) trim(lheoutput)//'.init'
        WRITE(*,*) trim(lheoutput)//'.evnt'
      END IF

C...Final SLHA file with spectrum and decay table.
      OPEN(UNIT=9,FILE=trim(slhaoutput)//'.spectrum.slha',STATUS='unknown')
      OPEN(UNIT=10,FILE=trim(slhaoutput)//'.decay.slha',STATUS='unknown')

C...Pythia log output.
      MSTU(11) = 11
      OPEN(UNIT=11,FILE=trim(txtoutput),STATUS='unknown')

C...Temporary files for initialization/event output.
      MSTP(161) = 12
      OPEN(UNIT=12,FILE=trim(lheoutput)//'.init',STATUS='unknown')
      MSTP(162) = 13
      OPEN(UNIT=13,FILE=trim(lheoutput)//'.evnt',STATUS='unknown')

C...Final Les Houches Event file, obtained by combining above two.
      MSTP(163) = 14
      OPEN(UNIT=14,FILE=trim(lheoutput),STATUS='unknown')

C...Main parameters of run: c.m. energy and number of events.
      ECM = sqrtSinGeV
      NEV = numevnt

C...Select SemiLeptonicRPV production processes.
      MSEL = 39                 ! turns on all MSSM processes except Higgs production
      IMSS( 1) = 1              ! generic SUSY scenario
      IMSS( 3) = 1              ! gluino is pole mass
      IMSS(23) = 9              ! write out spectrum table to SLHA file
      IMSS(24) = 10             ! write out decay table to SLHA file
      IMSS(51) = 0              ! RPV LLE off
      IMSS(52) = 3              ! RPV LQD on with user specified couplings
      IMSS(53) = 0              ! RPV UDD off
      IF (trim(coupling) .EQ. 'LQD231') THEN
        RVLAMP(2,3,1) = 0.005   ! LQD coupling
      ELSE IF (trim(coupling) .EQ. 'LQD233') THEN
        RVLAMP(2,3,3) = 0.005   ! LQD coupling
      END IF
      RMSS( 1) = 700.0          ! bino
      RMSS( 2) = 3000.0         ! wino
      RMSS( 3) = gluinomass     ! gluino
      RMSS( 4) = 3000.0         ! mu
      RMSS( 5) = 3.0            ! tan beta
      RMSS( 8) = squarkmass     ! left squark (1st-2nd generation)
      RMSS( 9) = squarkmass     ! right down squark (1st-2nd generation)
      RMSS(10) = squarkmass     ! left squark (3rd generation)
      RMSS(11) = squarkmass     ! right down squark (3rd generation)
      RMSS(12) = squarkmass     ! right up squark (3rd generation)
      RMSS( 6) = 3000.0         ! left slepton (1st-2nd generation)
      RMSS( 7) = 3000.0         ! right slepton (1st-2nd generation)
      RMSS(13) = 3000.0         ! left slepton (3rd generation)
      RMSS(14) = 3000.0         ! right slepton (3rd generation)
      RMSS(15) = 4800.0         ! bottom trilinear
      RMSS(16) = 533.3          ! top trilinear
      RMSS(17) = 4800.0         ! tau trilinear
      RMSS(18) = 0.0            ! Higgs mixing angle alpha
      RMSS(19) = 3000.0         ! pseudo-scalar Higgs mass

C...Initialize PYTHIA for LHC.
       CALL PYINIT('CMS','p','p',ECM)

C-----------------------------------------------------------------

C...Second section: event loop.

C...Begin event loop.
      DO 100 IEV = 1, NEV
        CALL PYUPEV
 100  CONTINUE

C-----------------------------------------------------------------

C...Third section: produce output and end.

C...Cross section table and partial decay widths.
      CALL PYSTAT(1)
      CALL PYSTAT(2)
      CALL PYUPIN

C...Produce final Les Houches Event File.
      CALL PYLHEF

      CLOSE(10)
      CLOSE(11)
      CLOSE(14)
      END
