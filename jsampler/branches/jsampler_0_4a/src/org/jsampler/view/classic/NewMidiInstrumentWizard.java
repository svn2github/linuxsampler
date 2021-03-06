/*
 *   JSampler - a java front-end for LinuxSampler
 *
 *   Copyright (C) 2005-2007 Grigor Iliev <grigor@grigoriliev.com>
 *
 *   This file is part of JSampler.
 *
 *   JSampler is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License version 2
 *   as published by the Free Software Foundation.
 *
 *   JSampler is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with JSampler; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 *   MA  02111-1307  USA
 */

package org.jsampler.view.classic;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JComboBox;
import javax.swing.JFileChooser;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.JSlider;
import javax.swing.JSpinner;
import javax.swing.JTextField;
import javax.swing.SpinnerNumberModel;

import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;

import net.sf.juife.Wizard;

import net.sf.juife.wizard.DefaultWizardModel;
import net.sf.juife.wizard.UserInputPage;
import net.sf.juife.wizard.WizardPage;

import org.jsampler.CC;
import org.jsampler.Instrument;
import org.jsampler.MidiInstrumentMap;
import org.jsampler.OrchestraModel;

import org.linuxsampler.lscp.MidiInstrumentInfo;
import org.linuxsampler.lscp.SamplerEngine;

import static org.jsampler.view.classic.ClassicI18n.i18n;


/**
 * A wizard for mapping new MIDI instrument.
 * @author Grigor Iliev
 */
public class NewMidiInstrumentWizard extends Wizard {
	
	/** Creates a new instance of <code>NewMidiInstrumentWizard</code>. */
	public
	NewMidiInstrumentWizard() {
		super(CC.getMainFrame(), i18n.getLabel("NewMidiInstrumentWizard.title"));
		setModel(new NewMidiInstrumentWizardModel());
	}
	
}

class NewMidiInstrumentWizardModel extends DefaultWizardModel {
	private final InstrLocationMethodWizardPage instrLocationMethodWizardPage =
		new InstrLocationMethodWizardPage();
	
	private final OrchestraSelectWizardPage orchestraSelectWizardPage =
		new OrchestraSelectWizardPage();
	
	private final ManualSelectWizardPage manualSelectWizardPage = new ManualSelectWizardPage();
	
	private final InstrumentMappingWizardPage instrumentMappingWizardPage =
		new InstrumentMappingWizardPage();
	
	NewMidiInstrumentWizardModel() {
		addPage(instrLocationMethodWizardPage);
		addStep(i18n.getLabel("NewMidiInstrumentWizard.step1"));
		
		addPage(manualSelectWizardPage);
		addPage(orchestraSelectWizardPage);
		addStep(i18n.getLabel("NewMidiInstrumentWizard.step2"), 2);
		
		addPage(instrumentMappingWizardPage);
		addStep(i18n.getLabel("NewMidiInstrumentWizard.step3"));
	}
	
		/**
	 * Moves to the next page in the wizard.
	 * @return The next page in the wizard.
	 */
	public WizardPage
	next() {
		InstrLocationMethodWizardPage p1 = instrLocationMethodWizardPage;
		WizardPage p2 = manualSelectWizardPage;
		
		if(getCurrentPage() == p1 && p1.isOrchestraMethodSelected()) {
			super.next();
		} else if(getCurrentPage() == manualSelectWizardPage) {
			super.next();
		}
		
		return super.next();
	}
	
	/**
	 * Moves to the previous page in the wizard.
	 * @return The previous page in the wizard.
	 * @see #hasPrevious
	 */
	public WizardPage
	previous() {
		InstrLocationMethodWizardPage p1 = instrLocationMethodWizardPage;
		WizardPage p2 = instrumentMappingWizardPage;
		
		if(getCurrentPage() == orchestraSelectWizardPage) {
			super.previous();
		} else if(getCurrentPage() == p2 && !p1.isOrchestraMethodSelected()) {
			super.previous();
		}
		
		return super.previous();
	}
	
	public void
	mapInstrument() {
		MidiInstrumentInfo instr = new MidiInstrumentInfo();
		if(instrLocationMethodWizardPage.isOrchestraMethodSelected()) {
			Instrument i = orchestraSelectWizardPage.getInstrument();
			instr.setFileName(i.getPath());
			instr.setInstrumentIndex(i.getInstrumentIndex());
			instr.setEngine(i.getEngine());
			instr.setLoadMode(orchestraSelectWizardPage.getLoadMode());
		} else {
			instr.setFileName(manualSelectWizardPage.getSelectedFile());
			instr.setInstrumentIndex(manualSelectWizardPage.getInstrumentIndex());
			instr.setEngine(manualSelectWizardPage.getEngine());
			instr.setLoadMode(manualSelectWizardPage.getLoadMode());
		}
		
		int map = instrumentMappingWizardPage.getMapId();
		int bank = instrumentMappingWizardPage.getMidiBank();
		int prog = instrumentMappingWizardPage.getMidiProgram();
		
		instr.setName(instrumentMappingWizardPage.getInstrumentName());
		instr.setVolume(instrumentMappingWizardPage.getVolume());
		
		CC.getSamplerModel().mapBackendMidiInstrument(map, bank, prog, instr);
	}
}

class InstrLocationMethodWizardPage extends UserInputPage {
	private final JRadioButton rbManual =
		new JRadioButton(i18n.getLabel("InstrLocationMethodWizardPage.rbManual"));
	
	private final JRadioButton rbOrchestra =
		new JRadioButton(i18n.getLabel("InstrLocationMethodWizardPage.rbOrchestra"));
	
	private final JCheckBox checkSkip =
		new JCheckBox(i18n.getLabel("InstrLocationMethodWizardPage.checkSkip"));
	
	InstrLocationMethodWizardPage() {
		super(i18n.getLabel("InstrLocationMethodWizardPage.subtitle"));
		
		String s = i18n.getLabel("InstrLocationMethodWizardPage.mainInstructions");
		setMainInstructions(s);
		
		JPanel p = new JPanel();
		p.setLayout(new BoxLayout(p, BoxLayout.Y_AXIS));
		
		ButtonGroup group = new ButtonGroup();
		group.add(rbManual);
		group.add(rbOrchestra);
		rbManual.setSelected(true);
		
		p.add(rbManual);
		p.add(rbOrchestra);
		
		JPanel p2 = new JPanel();
		p2.setLayout(new BorderLayout());
		p2.add(p, BorderLayout.NORTH);
		p2.add(checkSkip, BorderLayout.SOUTH);
		setMainPane(p2);
		
		switch(ClassicPrefs.getInstrLocationMethod()) {
		case 0:
			rbManual.setSelected(true);
			break;
		case 1:
			rbOrchestra.setSelected(true);
		}
		
		checkSkip.setSelected(ClassicPrefs.getNewMidiInstrWizardSkip1());
		
		rbManual.addActionListener(new ActionListener() {
			public void
			actionPerformed(ActionEvent e) {
				if(rbManual.isSelected()) ClassicPrefs.setInstrLocationMethod(0);
			}
		});
		
		rbOrchestra.addActionListener(new ActionListener() {
			public void
			actionPerformed(ActionEvent e) {
				if(rbOrchestra.isSelected()) ClassicPrefs.setInstrLocationMethod(1);
			}
		});
		
		checkSkip.addActionListener(new ActionListener() {
			public void
			actionPerformed(ActionEvent e) {
				ClassicPrefs.setNewMidiInstrWizardSkip1(checkSkip.isSelected());
			}
		});
	}
	
	/**
	 * Determines whether the user selected an orchestra location method.
	 */
	public boolean
	isOrchestraMethodSelected() { return rbOrchestra.isSelected(); }
}

class OrchestraSelectWizardPage extends UserInputPage {
	private final JLabel lOrchestras =
		new JLabel(i18n.getLabel("OrchestraSelectWizardPage.lOrchestras"));
	
	private final JLabel lInstruments =
		new JLabel(i18n.getLabel("OrchestraSelectWizardPage.lInstruments"));
	
	private final JLabel lLoadMode =
		new JLabel(i18n.getLabel("OrchestraSelectWizardPage.lLoadMode"));
	
	private final JComboBox cbOrchestras = new JComboBox();
	private final JComboBox cbInstruments = new JComboBox();
	private final JComboBox cbLoadMode = new JComboBox();
	
	OrchestraSelectWizardPage() {
		super(i18n.getLabel("OrchestraSelectWizardPage.subtitle"));
		setMainInstructions(i18n.getLabel("OrchestraSelectWizardPage.mainInstructions"));
		
		GridBagLayout gridbag = new GridBagLayout();
		GridBagConstraints c = new GridBagConstraints();
		
		JPanel p = new JPanel();
		
		p.setLayout(gridbag);
		
		c.fill = GridBagConstraints.NONE;
		
		c.gridx = 0;
		c.gridy = 0;
		c.anchor = GridBagConstraints.EAST;
		c.insets = new Insets(0, 0, 6, 16);
		gridbag.setConstraints(lOrchestras, c);
		p.add(lOrchestras); 
		
		c.gridx = 0;
		c.gridy = 1;
		gridbag.setConstraints(lInstruments, c);
		p.add(lInstruments);
		
		c.gridx = 0;
		c.gridy = 2;
		c.insets = new Insets(12, 0, 6, 16);
		gridbag.setConstraints(lLoadMode, c);
		p.add(lLoadMode);
		
		c.gridx = 1;
		c.gridy = 0;
		c.weightx = 1.0;
		c.insets = new Insets(0, 0, 6, 48);
		c.fill = GridBagConstraints.HORIZONTAL;
		c.anchor = GridBagConstraints.NORTH;
		gridbag.setConstraints(cbOrchestras, c);
		p.add(cbOrchestras); 
		
		c.gridx = 1;
		c.gridy = 1;
		gridbag.setConstraints(cbInstruments, c);
		p.add(cbInstruments);
		
		c.gridx = 1;
		c.gridy = 2;
		c.insets = new Insets(12, 0, 6, 48);
		gridbag.setConstraints(cbLoadMode, c);
		p.add(cbLoadMode);
		
		JPanel p2 = new JPanel();
		p2.setOpaque(false);
		c.gridx = 0;
		c.gridy = 3;
		c.fill = GridBagConstraints.VERTICAL;
		c.weightx = 0.0;
		c.weighty = 1.0;
		gridbag.setConstraints(p2, c);
		p.add(p2);
		
		setMainPane(p);
		
		cbOrchestras.addActionListener(new ActionListener() {
			public void
			actionPerformed(ActionEvent e) { orchestraChanged(); }
		});
		
		for(int i = 0; i < CC.getOrchestras().getOrchestraCount(); i++) {
			cbOrchestras.addItem(CC.getOrchestras().getOrchestra(i));
		}
		
		cbInstruments.addActionListener(new ActionListener() {
			public void
			actionPerformed(ActionEvent e) { instrumentChanged(); }
		});
		
		cbLoadMode.addItem(MidiInstrumentInfo.LoadMode.DEFAULT);
		cbLoadMode.addItem(MidiInstrumentInfo.LoadMode.ON_DEMAND);
		cbLoadMode.addItem(MidiInstrumentInfo.LoadMode.ON_DEMAND_HOLD);
		cbLoadMode.addItem(MidiInstrumentInfo.LoadMode.PERSISTENT);
	}
	
	private void
	orchestraChanged() {
		OrchestraModel om = (OrchestraModel)cbOrchestras.getSelectedItem();
		String s = om == null ? null : om.getDescription();
		if(s != null && s.length() == 0) s = null;
		cbOrchestras.setToolTipText(s);
		
		cbInstruments.removeAllItems();
		if(om == null || om.getInstrumentCount() == 0) {
			cbInstruments.setEnabled(false);
			return;
		}
		
		cbInstruments.setEnabled(true);
		
		for(int i = 0; i < om.getInstrumentCount(); i++) {
			cbInstruments.addItem(om.getInstrument(i));
		}
	}
	
	private void
	instrumentChanged() {
		Instrument instr = (Instrument)cbInstruments.getSelectedItem();
		String s = instr == null ? null : instr.getDescription();
		if(s != null && s.length() == 0) s = null;
		cbInstruments.setToolTipText(s);
		
		getWizard().enableNextButton(instr != null);
	}
	
	public void
	postinitPage() {
		getWizard().enableNextButton(cbInstruments.getSelectedItem() != null);
	}
	
	/**
	 * Gets the selected instrument.
	 */
	public Instrument
	getInstrument() { return (Instrument)cbInstruments.getSelectedItem(); }
	
	/**
	 * Gets the selected load mode.
	 */
	public MidiInstrumentInfo.LoadMode
	getLoadMode() { return (MidiInstrumentInfo.LoadMode) cbLoadMode.getSelectedItem(); }
}

class ManualSelectWizardPage extends UserInputPage {
	private final JLabel lFilename =
		new JLabel(i18n.getLabel("ManualSelectWizardPage.lFilename"));
	
	private final JLabel lIndex = new JLabel(i18n.getLabel("ManualSelectWizardPage.lIndex"));
	
	private final JLabel lEngine = new JLabel(i18n.getLabel("ManualSelectWizardPage.lEngine"));
	
	private final JLabel lLoadMode =
		new JLabel(i18n.getLabel("ManualSelectWizardPage.lLoadMode"));
	
	private final JTextField tfFilename = new JTextField();
	private final JSpinner spinnerIndex = new JSpinner(new SpinnerNumberModel(0, 0, 500, 1));
	
	private final JButton btnBrowse =
		new JButton(Res.iconFolderOpen16);
	
	private final JComboBox cbEngine = new JComboBox();
	private final JComboBox cbLoadMode = new JComboBox();
	
	ManualSelectWizardPage() {
		super(i18n.getLabel("ManualSelectWizardPage.subtitle"));
		setMainInstructions(i18n.getLabel("ManualSelectWizardPage.mainInstructions"));
		
		GridBagLayout gridbag = new GridBagLayout();
		GridBagConstraints c = new GridBagConstraints();
		
		JPanel mainPane = new JPanel();
		
		mainPane.setLayout(gridbag);
		
		c.fill = GridBagConstraints.NONE;
		
		c.gridx = 0;
		c.gridy = 0;
		c.anchor = GridBagConstraints.EAST;
		c.insets = new Insets(3, 3, 3, 3);
		gridbag.setConstraints(lFilename, c);
		mainPane.add(lFilename); 
		
		c.gridx = 0;
		c.gridy = 1;
		gridbag.setConstraints(lIndex, c);
		mainPane.add(lIndex);
		
		c.gridx = 0;
		c.gridy = 2;
		c.insets = new Insets(12, 3, 3, 3);
		gridbag.setConstraints(lEngine, c);
		mainPane.add(lEngine);
		
		c.gridx = 0;
		c.gridy = 3;
		c.insets = new Insets(3, 3, 3, 3);
		gridbag.setConstraints(lLoadMode, c);
		mainPane.add(lLoadMode);
		
		btnBrowse.setMargin(new Insets(0, 0, 0, 0));
		btnBrowse.setToolTipText(i18n.getLabel("ManualSelectWizardPage.btnBrowse"));
		c.gridx = 2;
		c.gridy = 0;
		gridbag.setConstraints(btnBrowse, c);
		mainPane.add(btnBrowse);
		
		c.fill = GridBagConstraints.HORIZONTAL;
		c.gridx = 1;
		c.gridy = 0;
		c.weightx = 1.0;
		c.anchor = GridBagConstraints.WEST;
		gridbag.setConstraints(tfFilename, c);
		mainPane.add(tfFilename);
			
		c.gridx = 1;
		c.gridy = 1;
		gridbag.setConstraints(spinnerIndex, c);
		mainPane.add(spinnerIndex);
		
		c.gridx = 1;
		c.gridy = 2;
		c.insets = new Insets(12, 3, 3, 64);
		gridbag.setConstraints(cbEngine, c);
		mainPane.add(cbEngine);
		
		c.gridx = 1;
		c.gridy = 3;
		c.insets = new Insets(3, 3, 3, 64);
		gridbag.setConstraints(cbLoadMode, c);
		mainPane.add(cbLoadMode);
		
		JPanel p2 = new JPanel();
		p2.setOpaque(false);
		c.gridx = 0;
		c.gridy = 4;
		c.fill = GridBagConstraints.VERTICAL;
		c.weightx = 0.0;
		c.weighty = 1.0;
		gridbag.setConstraints(p2, c);
		mainPane.add(p2);
		
		setMainPane(mainPane);
		
		tfFilename.getDocument().addDocumentListener(getHandler());
		
		btnBrowse.addActionListener(new ActionListener() {
			public void
			actionPerformed(ActionEvent e) { onBrowse(); }
		});
		
		for(SamplerEngine e : CC.getSamplerModel().getEngines()) cbEngine.addItem(e);
		
		cbLoadMode.addItem(MidiInstrumentInfo.LoadMode.DEFAULT);
		cbLoadMode.addItem(MidiInstrumentInfo.LoadMode.ON_DEMAND);
		cbLoadMode.addItem(MidiInstrumentInfo.LoadMode.ON_DEMAND_HOLD);
		cbLoadMode.addItem(MidiInstrumentInfo.LoadMode.PERSISTENT);
	}
	
	private void
	onBrowse() {
		JFileChooser fc = new JFileChooser();
		int result = fc.showOpenDialog(this);
		if(result == JFileChooser.APPROVE_OPTION) {
			tfFilename.setText(fc.getSelectedFile().getPath());
		}
	}
	
	private void
	updateState() { getWizard().enableNextButton(tfFilename.getText().length() != 0); }
	
	public void
	postinitPage() {
		updateState();
	}
	
	/**
	 * Gets the name of the instrument file.
	 * @return The name of the instrument file.
	 */
	public String
	getSelectedFile() { return tfFilename.getText(); }
	
	/**
	 * Gets the index of the instrument in the instrument file.
	 * @return The index of the instrument in the instrument file.
	 */
	public int
	getInstrumentIndex() { return Integer.parseInt(spinnerIndex.getValue().toString()); }
	
	/**
	 * Gets the selected engine.
	 */
	public String
	getEngine() { return ((SamplerEngine)cbEngine.getSelectedItem()).getName(); }
	
	/**
	 * Gets the selected load mode.
	 */
	public MidiInstrumentInfo.LoadMode
	getLoadMode() { return (MidiInstrumentInfo.LoadMode)cbLoadMode.getSelectedItem(); }
	
	private final Handler eventHandler = new Handler();
	
	private Handler
	getHandler() { return eventHandler; }
	
	private class Handler implements DocumentListener {
		// DocumentListener
		public void
		insertUpdate(DocumentEvent e) { updateState(); }
		
		public void
		removeUpdate(DocumentEvent e) { updateState(); }
		
		public void
		changedUpdate(DocumentEvent e) { updateState(); }
	}
}

class InstrumentMappingWizardPage extends WizardPage  {
	private final JLabel lName = new JLabel(i18n.getLabel("InstrumentMappingWizardPage.lName"));
	private final JLabel lMap = new JLabel(i18n.getLabel("InstrumentMappingWizardPage.lMap"));
	private final JLabel lBank = new JLabel(i18n.getLabel("InstrumentMappingWizardPage.lBank"));
	private final JLabel lProgram =
		new JLabel(i18n.getLabel("InstrumentMappingWizardPage.lProgram"));
	
	private final JLabel lVolume =
		new JLabel(i18n.getLabel("InstrumentMappingWizardPage.lVolume"));
	
	private final JTextField tfName = new JTextField();
	private final JComboBox cbMap = new JComboBox();
	private final JSpinner spinnerBank = new JSpinner(new SpinnerNumberModel(0, 0, 16383, 1));
	private final JComboBox cbProgram = new JComboBox();
	private final JSlider slVolume = new JSlider(0, 100, 100);
	
	InstrumentMappingWizardPage() {
		super(i18n.getLabel("InstrumentMappingWizardPage.subtitle"));
		setPageType(Type.CONFIRMATION_PAGE);
		
		GridBagLayout gridbag = new GridBagLayout();
		GridBagConstraints c = new GridBagConstraints();
		
		setLayout(gridbag);
		
		c.fill = GridBagConstraints.NONE;
		
		c.gridx = 0;
		c.gridy = 0;
		c.anchor = GridBagConstraints.EAST;
		c.insets = new Insets(24, 3, 3, 0);
		gridbag.setConstraints(lName, c);
		add(lName); 
		
		c.gridx = 0;
		c.gridy = 2;
		c.insets = new Insets(3, 3, 3, 0);
		gridbag.setConstraints(lMap, c);
		add(lMap);
		
		c.gridx = 0;
		c.gridy = 3;
		gridbag.setConstraints(lBank, c);
		add(lBank);
		
		c.gridx = 0;
		c.gridy = 4;
		gridbag.setConstraints(lProgram, c);
		add(lProgram);
		
		c.gridx = 0;
		c.gridy = 1;
		c.insets = new Insets(3, 3, 24, 0);
		gridbag.setConstraints(lVolume, c);
		add(lVolume);
		
		c.fill = GridBagConstraints.HORIZONTAL;
		c.gridx = 1;
		c.gridy = 0;
		c.weightx = 1.0;
		c.insets = new Insets(24, 12, 3, 36);
		c.anchor = GridBagConstraints.WEST;
		gridbag.setConstraints(tfName, c);
		add(tfName);
			
		c.gridx = 1;
		c.gridy = 2;
		c.insets = new Insets(3, 12, 3, 36);
		gridbag.setConstraints(cbMap, c);
		add(cbMap);
		
		c.gridx = 1;
		c.gridy = 3;
		gridbag.setConstraints(spinnerBank, c);
		add(spinnerBank);
		
		c.gridx = 1;
		c.gridy = 4;
		gridbag.setConstraints(cbProgram, c);
		add(cbProgram);
		
		c.gridx = 1;
		c.gridy = 1;
		c.insets = new Insets(3, 12, 24, 36);
		gridbag.setConstraints(slVolume, c);
		add(slVolume);
		
		JPanel p2 = new JPanel();
		p2.setOpaque(false);
		c.gridx = 0;
		c.gridy = 5;
		c.insets = new Insets(0, 0, 0, 0);
		c.fill = GridBagConstraints.VERTICAL;
		c.weightx = 0.0;
		c.weighty = 1.0;
		gridbag.setConstraints(p2, c);
		add(p2);
		
		cbMap.addActionListener(new ActionListener() {
			public void
			actionPerformed(ActionEvent e) { updateState(); }
		});
		
		for(MidiInstrumentMap m : CC.getSamplerModel().getMidiInstrumentMaps()) {
			cbMap.addItem(m);
		}
		
		tfName.getDocument().addDocumentListener(getHandler());
		
		cbMap.setEnabled(cbMap.getItemCount() > 0);
		
		
		for(int i = 0; i < 128; i++) cbProgram.addItem(new Integer(i));
	}
	
	private void
	updateState() {
		cbMap.setEnabled(cbMap.getItemCount() > 0);
		boolean b = cbMap.getSelectedItem() != null;
		spinnerBank.setEnabled(b);
		cbProgram.setEnabled(b);
		
		b = tfName.getText().length() > 0 && cbMap.getSelectedItem() != null;
		b = b && cbProgram.getSelectedItem() != null;
		if(getWizard() != null) getWizard().enableFinishButton(b);
	}
	
	public void
	postinitPage() {
		updateState();
	}
	
	/**
	 * Invoked when the user clicks the 'Finish' button
	 * while this page is the current page of the wizard.
	 * @return <code>true</code>
	 */
	public boolean
	mayFinish() {
		((NewMidiInstrumentWizardModel)getWizardModel()).mapInstrument();
		return true;
	}
	
	/**
	 * Gets the ID of the selected MIDI instrument map.
	 */
	public int
	getMapId() { return ((MidiInstrumentMap)cbMap.getSelectedItem()).getMapId(); }
	
	/**
	 * Gets the selected MIDI bank.
	 */
	public int
	getMidiBank() { return Integer.parseInt(spinnerBank.getValue().toString()); }
	
	/**
	 * Gets the selected MIDI program.
	 */
	public int
	getMidiProgram() { return cbProgram.getSelectedIndex(); }
	
	/**
	 * Gets the chosen name for the new MIDI instrument.
	 * @return The chosen name for the new MIDI instrument.
	 */
	public String
	getInstrumentName() { return tfName.getText(); }
	
	/**
	 * Returns the volume level of the new MIDI instrument.
	 * @return The volume level of the new MIDI instrument.
	 */
	public float
	getVolume() {
		float f = slVolume.getValue();
		f /= 100;
		return f;
	}
	
	private final Handler eventHandler = new Handler();
	
	private Handler
	getHandler() { return eventHandler; }
	
	private class Handler implements DocumentListener {
		// DocumentListener
		public void
		insertUpdate(DocumentEvent e) { updateState(); }
		
		public void
		removeUpdate(DocumentEvent e) { updateState(); }
		
		public void
		changedUpdate(DocumentEvent e) { updateState(); }
	}
}
