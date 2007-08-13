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

package org.jsampler.view.std;

import java.awt.Dimension;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import java.io.File;

import javax.swing.BorderFactory;
import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSpinner;
import javax.swing.JTextField;
import javax.swing.SpinnerNumberModel;

import org.jsampler.CC;
import org.jsampler.JSPrefs;

import static org.jsampler.view.std.StdI18n.i18n;
import static org.jsampler.view.std.StdPrefs.*;


/**
 *
 * @author Grigor Iliev
 */
public class JSGeneralProps {
	
	/** Creates a new instance of <code>JSGeneralProps</code> */
	private JSGeneralProps() { }
	
	private static JSPrefs
	preferences() { return CC.getViewConfig().preferences(); }
	
	
	public static class JSamplerHomePane extends JPanel {
		private final JTextField tfJSamplerHome = new JTextField();
		private final JButton btnChange =
			new JButton(i18n.getButtonLabel("JSGeneralProps.btnChange"));
		
		public
		JSamplerHomePane() {
			setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
			
			JPanel p = new JPanel();
			p.setLayout(new BoxLayout(p, BoxLayout.X_AXIS));
			
			if(CC.getJSamplerHome() != null) {
				tfJSamplerHome.setText(CC.getJSamplerHome());
			}
			
			Dimension d;
			d = new Dimension(Short.MAX_VALUE, tfJSamplerHome.getPreferredSize().height);
			tfJSamplerHome.setMaximumSize(d);
			p.add(tfJSamplerHome);
			p.add(Box.createRigidArea(new Dimension(5, 0)));
			p.add(btnChange);
			p.setBorder(BorderFactory.createEmptyBorder(2, 6, 6, 6));
			p.setAlignmentX(JPanel.CENTER_ALIGNMENT);
			add(p);
			
			String s = i18n.getLabel("JSGeneralProps.jSamplerHome");
			setBorder(BorderFactory.createTitledBorder(s));
			setMaximumSize(new Dimension(Short.MAX_VALUE, getPreferredSize().height));
			setAlignmentX(JPanel.LEFT_ALIGNMENT);
			
			btnChange.addActionListener(new ActionListener() {
				public void
				actionPerformed(ActionEvent e) { onChange(); }
			});
		}
		
		private void
		onChange() {
			JFileChooser fc = new JFileChooser();
			fc.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
			int result = fc.showOpenDialog(this);
			if(result != JFileChooser.APPROVE_OPTION) return;
			
			String s = CC.getJSamplerHome();
			String suf = File.separator + ".jsampler";
			if(s != null) suf = File.separator + new File(s).getName();
			
			tfJSamplerHome.setText(fc.getSelectedFile().getPath() + suf);
		}
		
		/**
		 * Gets the selected JSampler's home directory.
		 */
		public String
		getJSamplerHome() { return tfJSamplerHome.getText(); }
	}
	
	
	public static class RecentScriptsPane extends JPanel {
		private final JLabel lRecentScriptsSize =
			new JLabel(i18n.getLabel("JSGeneralProps.lRecentScriptsSize"));
		
		private final JSpinner spRecentScriptsSize;
		
		private final JButton btnClearRecentScriptList =
			new JButton(i18n.getButtonLabel("JSGeneralProps.btnClearRecentScriptList"));
	
		public
		RecentScriptsPane() {
			setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
			
			int i = preferences().getIntProperty(RECENT_LSCP_SCRIPTS_SIZE);
			spRecentScriptsSize = new JSpinner(new SpinnerNumberModel(i, 0, 100, 1));
			spRecentScriptsSize.setMaximumSize(spRecentScriptsSize.getPreferredSize());
			
			JPanel p = new JPanel();
			p.setLayout(new BoxLayout(p, BoxLayout.X_AXIS));
			p.add(lRecentScriptsSize);
			p.add(Box.createRigidArea(new Dimension(5, 0)));
			p.add(spRecentScriptsSize);
			
			p.setAlignmentX(JPanel.CENTER_ALIGNMENT);
			add(p);
			
			add(Box.createRigidArea(new Dimension(0, 6)));
			
			btnClearRecentScriptList.addActionListener(new ActionListener() {
				public void
				actionPerformed(ActionEvent e) {
					preferences().setStringProperty(RECENT_LSCP_SCRIPTS, null);
					clearRecentScripts();
				}
			});
			
			btnClearRecentScriptList.setAlignmentX(JPanel.CENTER_ALIGNMENT);
			add(btnClearRecentScriptList);
			add(Box.createRigidArea(new Dimension(0, 6)));
			
			setMaximumSize(new Dimension(Short.MAX_VALUE, getPreferredSize().height));
			setAlignmentX(JPanel.LEFT_ALIGNMENT);
			String s = i18n.getLabel("JSGeneralProps.recentScripts");
			setBorder(BorderFactory.createTitledBorder(s));
		}
		
		/**
		 * Override this method to clear the recent scripts.
		 */
		protected void
		clearRecentScripts() { }
		
		public int
		getRecentScriptsSize() {
			return Integer.parseInt(spRecentScriptsSize.getValue().toString());
		}
	}
}