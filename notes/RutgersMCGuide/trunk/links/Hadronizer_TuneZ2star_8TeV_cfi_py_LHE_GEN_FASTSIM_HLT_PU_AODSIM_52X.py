# Auto generated configuration file
# using:
# Revision: 1.372.2.14
# Source: /local/reps/CMSSW/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v
# with command line options: Configuration/GenProduction/Hadronizer_MgmMatchTuneZ2star_8TeV_cff.py --filetype=LHE --filein=file:MYFILE.lhe --step=GEN,FASTSIM,HLT:GRun --pileup=2012_Summer_inTimeOnly --geometry=DB --beamspot=Realistic8TeVCollision --conditions=auto:startup --eventcontent=AODSIM --datatier=GEN-SIM-DIGI-AODSIM --number=5000 --mc --no_exec --python_filename=Hadronizer_TuneZ2star_8TeV_cfi_py_LHE_GEN_FASTSIM_HLT_PU_AODSIM_52X.py
import sys
import FWCore.ParameterSet.Config as cms

process = cms.Process('HLT')

# Import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('FastSimulation.Configuration.EventContent_cff')
process.load('FastSimulation.Configuration.FamosSequences_cff')
process.load('FastSimulation.PileUpProducer.PileUpSimulator_2012_Summer_inTimeOnly_cff')
process.load('FastSimulation.Configuration.Geometries_START_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Generator_cff')
process.load('GeneratorInterface.Core.genFilterSummary_cff')
process.load('IOMC.EventVertexGenerators.VtxSmearedParameters_cfi')
process.load('HLTrigger.Configuration.HLT_GRun_Famos_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

TAG = sys.argv[2]
NAMEONE = sys.argv[3]
MASSONE = sys.argv[4]
NAMETWO = sys.argv[5]
MASSTWO = sys.argv[6]
NUMBER = sys.argv[7]
NAMETHREE = sys.argv[8]
JOB = sys.argv[9]
EVENTS = sys.argv[10]
STOREDIR = sys.argv[11]

MAXEVENTS = 1000

INPUTFILENAME = 'file:'+STOREDIR+'/lhe/'+TAG+'_'+NAMEONE+MASSONE+'_'+NAMETWO+MASSTWO+'_'+NUMBER+'_hh_'+NAMETHREE+'.lhe'
OUTPUTFILENAME = STOREDIR+'/aodsim/'+TAG+'_'+NAMEONE+MASSONE+'_'+NAMETWO+MASSTWO+'_'+NUMBER+'_hh_'+NAMETHREE+'_TuneZ2star_8TeV-madgraph5-pythia6_PU_S10_START52_V10_FastSim-v1_'+JOB+'_aodsim.root'

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(MAXEVENTS)
)

# Input source
process.source = cms.Source("LHESource",
    fileNames = cms.untracked.vstring(
        INPUTFILENAME
    ),
    firstRun   = cms.untracked.uint32(int(NUMBER)),
    firstEvent = cms.untracked.uint32(int(EVENTS)),
    skipEvents = cms.untracked.uint32(int(EVENTS)-1)
)

process.options = cms.untracked.PSet(

)

# Production info
process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.372.2.14 $'),
    annotation = cms.untracked.string('Configuration/GenProduction/Hadronizer_MgmMatchTuneZ2star_8TeV_cff.py nevts:5000'),
    name = cms.untracked.string('PyReleaseValidation')
)

# Output definition
process.AODSIMoutput = cms.OutputModule("PoolOutputModule",
    eventAutoFlushCompressedSize = cms.untracked.int32(15728640),
    outputCommands = process.AODSIMEventContent.outputCommands,
    fileName = cms.untracked.string(
        OUTPUTFILENAME
    ),
    dataset = cms.untracked.PSet(
        filterName = cms.untracked.string(''),
        dataTier = cms.untracked.string('GEN-SIM-DIGI-AODSIM')
    ),
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('mypath')
    )
)

# Additional output definition

# Other statements
process.famosSimHits.SimulateCalorimetry = True
process.famosSimHits.SimulateTracking = True
process.simulation = cms.Sequence(process.simulationWithFamos)
process.HLTEndSequence = cms.Sequence(process.reconstructionWithFamos)
process.Realistic8TeVCollisionVtxSmearingParameters.type = cms.string("BetaFunc")
process.famosSimHits.VertexGenerator = process.Realistic8TeVCollisionVtxSmearingParameters
process.famosPileUp.VertexGenerator = process.Realistic8TeVCollisionVtxSmearingParameters

# Customise the HLT menu for running on MC
from HLTrigger.Configuration.customizeHLTforMC import customizeHLTforMC
process = customizeHLTforMC(process)

process.GlobalTag.globaltag = 'START52_V10::All'

process.generator = cms.EDFilter("Pythia6HadronizerFilter",
    pythiaPylistVerbosity = cms.untracked.int32(1),
    pythiaHepMCVerbosity = cms.untracked.bool(True),
    filterEfficiency = cms.untracked.double(1.0),
    crossSection = cms.untracked.double(-1),
    comEnergy = cms.double(8000.0),
    maxEventsToPrint = cms.untracked.int32(0),
    PythiaParameters = cms.PSet(
        pythiaUESettings = cms.vstring(
            'MSTU(21) = 1       ! Check on possible errors during program execution',
            'MSTJ(22) = 2       ! Decay those unstable particles',
            'PARJ(71) = 10.     ! for which ctau  10 mm',
            'MSTP(33) = 0       ! no K factors in hard cross sections',
            'MSTP(2)  = 1       ! which order running alphaS',
            'MSTP(51) = 10042   ! structure function chosen (external PDF CTEQ6L1)',
            'MSTP(52) = 2       ! work with LHAPDF',
            'PARP(82) = 1.921   ! pt cutoff for multiparton interactions',
            'PARP(89) = 1800.   ! sqrts for which PARP82 is set',
            'PARP(90) = 0.227   ! Multiple interactions: rescaling power',
            'MSTP(95) = 6       ! CR (color reconnection parameters)',
            'PARP(77) = 1.016   ! CR',
            'PARP(78) = 0.538   ! CR',
            'PARP(80) = 0.1     ! Prob. colored parton from BBR',
            'PARP(83) = 0.356   ! Multiple interactions: matter distribution parameter',
            'PARP(84) = 0.651   ! Multiple interactions: matter distribution parameter',
            'PARP(62) = 1.025   ! ISR cutoff',
            'MSTP(91) = 1       ! Gaussian primordial kT',
            'PARP(93) = 10.0    ! primordial kT-max',
            'MSTP(81) = 21      ! multiple parton interactions 1 is Pythia default',
            'MSTP(82) = 4       ! Defines the multi-parton model'),
        processParameters = cms.vstring(
            'MSEL = 0           ! User defined processes',
            'PMAS(5,1) = 4.8    ! b quark mass',
            'PMAS(6,1) = 172.5  ! t quark mass',
            'MSTJ(1)  = 1       ! Fragmentation/hadronization on or off',
            'MSTP(61) = 1       ! Parton showering on or off'),
        parameterSets = cms.vstring(
            'pythiaUESettings',
            'processParameters')
    )
)

process.multileptonFilter = cms.EDFilter('MultiLeptonFilter',
    src = cms.InputTag("genParticles"),
    edfilterOn = cms.bool(True),
    multlepFilterOn = cms.bool(True),
    mixModeFilterOn = cms.bool(False),
    nLepton = cms.int32(2),
    debug = cms.bool(False)
)

process.myfilter = cms.Sequence(process.multileptonFilter)

process.mypath = cms.Path(process.myfilter*process.reconstructionWithFamos)

# Path and EndPath definitions
process.generation_step = cms.Path(process.pgen_genonly)
process.reconstruction = cms.Path(process.reconstructionWithFamos)
process.genfiltersummary_step = cms.EndPath(process.genFilterSummary)
process.AODSIMoutput_step = cms.EndPath(process.AODSIMoutput)

# Schedule definition
#process.schedule = cms.Schedule(process.generation_step,process.genfiltersummary_step)
#process.schedule.extend(process.HLTSchedule)
#process.schedule.extend([process.reconstruction,process.AODSIMoutput_step])

# filter all path with the production filter sequence
for path in process.paths:
        getattr(process,path)._seq = process.generator * process.genParticles * process.myfilter * getattr(process,path)._seq
